#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import imp
import os
import protocol
import socket
import struct
import sys
import traceback
import ctypes

from os.path import dirname, realpath, join

enableTraceMessages = True
enableVerboseTraceMessages = False

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)
helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')

helperlib = imp.load_source('helperlib', helperLibPath)

ScriptsDir = "<DSC_SCRIPT_PATH>"
VarDir = "<PYTHON_PID_DIR>"

def trace(text):
    if enableTraceMessages:
        sys.stdout.write(text + '\n')

def verbose_trace(text):
    if enableVerboseTraceMessages:
        trace(text)

def read_uchar (fd):
    verbose_trace('<read_uchar>')

    buf = fd.recv(1)
    if len(buf) < 1:
        return None

    val = struct.unpack('@B',buf)[0]

    verbose_trace('  val: '+ str(int(val)))
    verbose_trace('</read_uchar>')

    return val

def read_request(fd):
    verbose_trace('<read_request>')

    op_type = read_uchar(fd)
    if op_type == None:
        return None
    verbose_trace('  op_type: ' + str(op_type))

    op_name = protocol.read_string(fd)
    verbose_trace('  op_name: "' + op_name + '"')

    d = protocol.read_values(fd)
    verbose_trace('</read_request>')

    return (op_type, op_name, d)

def write_int(fd, val):
    verbose_trace('<write_int>')
    verbose_trace('  val: '+str(val))

    buf = struct.pack('@i', val)
    fd.send(buf)

    verbose_trace('</write_int>')

def write_success(fd, args = None):
    trace('<write_success>')

    write_int(fd, 0)
    if args is not None:
        protocol.write_values(fd, args)

    trace('</write_success>')

def write_failed(s, fail_code, text=''):
    trace('<write_failed>')

    write_int(s, fail_code)
    protocol.write_string(s, text)

    trace('</write_failed>')

def translate_input(d):
    """ This method is a convenience for a protocol change and should be
        removed when the handlers are updated."""
    verbose_trace('<translate_input>')

    oldStyleD = dict()
    if sys.version > '2.9':
        for key, value in d.items():
            if type(key) != str:
                key = str(key)
            if hasattr(value,'value') and hasattr(value.value,'value'):
                oldStyleD[key] = value.value.value
            else:
                oldStyleD[key] = value.value
    else:
        for key, value in d.iteritems():
            if type(key) != str:
                key = str(key)
            if hasattr(value,'value') and hasattr(value.value,'value'):
                oldStyleD[key] = value.value.value
            else:
                oldStyleD[key] = value.value

    verbose_trace('</translate_input>')
    return oldStyleD

def callMOF(req):
    oldStyleDict = translate_input(req[2])
    trace ('MOF=' + repr((req[0], req[1], oldStyleDict)))

    op = ('Test', 'Set', 'Get', 'Inventory')

    if req[1] not in globals().keys():
        sys.stderr.write('Unable to find module: ' + req[1])
        return None

    the_module = globals()[req[1]]
    method_name = op[req[0]] + '_Marshall'

    if not method_name in the_module.__dict__.keys():
        sys.stderr.write('Unable to find method: ' + method_name)
        return None

    trace('calling '+ req[1] + '.' + method_name + ' ' + repr (oldStyleDict))
    ret = the_module.__dict__[method_name](**oldStyleDict)
    sys.stderr.write(repr(ret))

    return ret
    
def handle_request(fd, req):
    trace('<handle_request>')

    requestResult = callMOF(req)
    if len(requestResult) < 2 :
        ret = None
        rval = requestResult[0]
    else:
        rval = requestResult[0]
        ret = requestResult[1]

    if rval == 0:
        write_success(fd, ret)
    else:
        write_failed(fd, 1, 'Error occurred processing '+ repr(req))

    trace('</handle_request>')

def main(argv):
    default_timeout_sec = 85
    socket.setdefaulttimeout(default_timeout_sec)
    fd = socket.fromfd(int(argv[1]), socket.AF_UNIX, socket.SOCK_STREAM)
    read = 1
    out = ''

    while 0 < read:
        try:
            req = read_request(fd)
            if req == None:
                read = -1
            else:
                trace('Main: request len is '+ str(len(req)))
                handle_request(fd, req)
        except socket.error:
            read = -1;
            sys.stderr.write('exception encountered')

##############################
try:
    trace('Socket: ' + str(sys.argv[1]))
    
    pid_path = VarDir + '/run/python/' + repr(os.getuid())
    
    if not os.path.isdir(pid_path):
        os.system('mkdir -p ' + pid_path)

    pid_file = pid_path + '/dsc_python_client.pid'

    try:        
        pidFileHandle = open(pid_file, 'w')
        pidFileHandle.write(str(os.getpid()) + "\n")
        pidFileHandle.flush()
        pidFileHandle.close()
    except:
        sys.stderr.write('Unable to create ' + pid_file)

    # Put the cwd (current working directory) in the system path so we can find our module
    sys.path.insert(0, '')

    # Find the name of the version specific scripts folder for the version of Python on the machine
    trace('Using python version '+ sys.version)
    if sys.version < '2.6':
        versionSpecificFolderName = '2.4x-2.5x'
    elif sys.version < '3':
        versionSpecificFolderName = '2.6x-2.7x'
    else:
        versionSpecificFolderName = '3.x'

    # Go to the version specific scripts folder for the version of Python on the machine
    versionSpecificFolderPath = join(pathToCommonScriptsFolder, versionSpecificFolderName)
    trace(versionSpecificFolderPath)
    os.chdir(versionSpecificFolderPath)

    # Import all scripts from the version specific scripts folder
    from Scripts import *
    
    # Open the socket and listen for requests
    if __name__ == '__main__':
        main(sys.argv)
except:
    sys.stderr.write('\nException: ')
    sys.stderr.write(repr(sys.exc_info()) + '\n')
    traceback.print_tb(sys.exc_info()[2])
    sys.stderr.write('\n')
finally:
    # Close the socket
    sys.stderr.write('Exiting - closing socket\n')
    (socket.fromfd(int (sys.argv[1]), socket.AF_UNIX, socket.SOCK_STREAM)).close()
