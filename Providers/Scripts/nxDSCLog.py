#!/usr/bin/env python
# ============================================================================
#  Copyright (C) Microsoft Corporation, All rights reserved.
# ============================================================================

import os
from os.path import exists, join, realpath, split
import sys
import time
import inspect
import codecs
import imp

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder, currentFileName = split(pathToCurrentScript)
helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')

helperlib = imp.load_source('helperlib', helperLibPath)

def write_error_to_stderr(message):
    sys.stderr.write(message + '\n')

def open_file_with_error_catch(filePath, mode = 'r'):
    """ This context ensures the file is closed. """

    try:
        fileHandle = codecs.open(filePath, mode, 'utf8')
    except:
        return None, Exception('IOError')
    
    return fileHandle, None

class DSCLog(object):
    def __init__(self):
        self.levels = ['FATAL', 'ERROR', 'WARNING', 'INFO', 'DEBUG', 'VERBOSE']
        self.current_level = 5

        logFileParentPath = helperlib.PYTHON_PID_DIR
        logFileName = helperlib.CONFIG_SYSCONFDIR_DSC + '.log'

        if helperlib.CONFIG_SYSCONFDIR_DSC == "dsc":
            logFileParentPath = join(logFileParentPath, 'log')
            directoryOrFileExistsAtPath = exists(logFileParentPath)
            if not exists(logFileParentPath):
                os.makedirs(logFileParentPath)

        self.file_path = join(logFileParentPath, logFileName)

    def Log(self, log_level, message):
        last_frame = inspect.currentframe().f_back
        place = last_frame.f_globals['__file__'] + '(' + str(last_frame.f_lineno) + ')'
        
        if message is None or len(message) < 1:
            return

        if log_level is None:
            log_level = self.current_level

        if type(log_level) == str:
            try:
                self.levels.index(log_level)
            except:
                return
        else if log_level < 0 or log_level >= len(self.levels):
            return

        if log_level > self.current_level:
            return

        currentTime = time.localtime()

        # YYYY/MM/DD HH:MM:SS: LEVEL: FILE(LINE): \n message \n
        logLine = "%04u/%02u/%02u %02u:%02u:%02u: %s: %s:\n%s\n" % (currentTime.tm_year,
            currentTime.tm_mon,
            currentTime.tm_mday,
            currentTime.tm_hour,
            currentTime.tm_min,
            currentTime.tm_sec,
            self.levels[log_level],
            place,
            message)

        error = None

        try:
            logFileHandle, error = open_file_with_error_catch(self.file_path, 'a')

            if error:
                write_error_to_stderr("Exception opening logfile " + self.file_path + " Error: " + str(error))
            else:
                logFileHandle.write(logLine)
        except:
            write_error_to_stderr("Exception opening logfile " + self.file_path + " Error: " + str(error))
        finally:
            logFileHandle.close()
