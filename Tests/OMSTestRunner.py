#!/usr/bin/python
import os
import os.path
import subprocess
import sys

pathToCurrentScript = os.path.realpath(__file__)
pathToTestsFolder = os.path.dirname(pathToCurrentScript)
pathToScriptE2ETestsFolder = os.path.join(pathToTestsFolder, 'script_e2e_tests')

def usage():
    print("sudo OMSTestRunner.py omsAgentPackageLocation omsWorkspaceID, omsWorkspaceKey")
    sys.exit(1)

def retrieveOMSAgentFromURL(url):
    print("Retrieving OMS Agent from URL " + url)

def removeOMSAgent(omsAgentPackageLocation):
    print("Removing OMS Agent from location " + omsAgentPackageLocation)

    omsAgentRemoveCommand = "sudo " + omsAgentPackageLocation + " --remove"
    omsAgentRemoveProcess = subprocess.Popen(omsAgentRemoveCommand, shell = True)
    omsAgentRemoveReturnCode = omsAgentRemoveProcess.wait()
    return omsAgentRemoveReturnCode

def installOMSAgent(omsAgentPackageLocation, omsWorkspaceID, omsWorkspaceKey):
    print("Installing OMS Agent from location " + omsAgentPackageLocation + " under the workspace ID " + omsWorkspaceID)

    omsAgentInstallCommand = "sudo " + omsAgentPackageLocation + " --upgrade -w " + omsWorkspaceID + " -s " + omsWorkspaceKey
    omsAgentInstallProcess = subprocess.Popen(omsAgentInstallCommand, shell = True)
    omsAgentInstallReturnCode = omsAgentInstallProcess.wait()
    return omsAgentInstallReturnCode

def upgradeOMSAgent(oldOmsAgentPackageLocation, newOmsAgentPackageLocation, omsWorkspaceID, omsWorkspaceKey):
    print("Upgrading OMS Agent")

    omsAgentRemoveReturnCode = removeOMSAgent(oldOmsAgentPackageLocation)
    if omsAgentRemoveReturnCode != 0:
        return omsAgentRemoveReturnCode

    omsAgentInstallReturnCode = installOMSAgent(newOmsAgentPackageLocation, omsWorkspaceID, omsWorkspaceKey)
    return omsAgentInstallReturnCode

def runScriptE2ETest(testPath):
    runTestCommand = "sudo " + testPath
    runTestProcess = subprocess.Popen(runTestCommand, shell = True)
    runTestReturnCode = runTestProcess.wait()
    return runTestReturnCode

def runAllScriptE2ETests():
    print("Running end to end tests")
    
    allTestsPassed = True

    scriptE2ETestFolderChildren = os.listdir(pathToScriptE2ETestsFolder)
    for scriptE2ETestFolderChildName in scriptE2ETestFolderChildren:
        childPath = os.path.join(pathToScriptE2ETestsFolder, scriptE2ETestFolderChildName)
        if (os.path.isfile(childPath) and scriptE2ETestFolderChildName[-3:] == '.py'):
            runTestReturnCode = runScriptE2ETest(childPath)

            if (runTestReturnCode != 0):
                print ("FAILED: " + childPath)
                allTestsPassed = False

    return allTestsPassed

def main(argv):
    if len(argv) < 3:
        usage()

    omsAgentPackageLocation = os.path.join(pathToTestsFolder, argv[0])
    omsWorkspaceID = argv[1]
    omsWorkspaceKey = argv[2]

    upgradeOMSAgentReturnCode = upgradeOMSAgent(omsAgentPackageLocation, omsAgentPackageLocation, omsWorkspaceID, omsWorkspaceKey)
    if upgradeOMSAgentReturnCode != 0:
        print ("OMS Agent upgrade failed with return code " + str(upgradeOMSAgentReturnCode))
        sys.exit(1)

    testsPassed = runAllScriptE2ETests()
    if testsPassed:
        print ("TESTS SUCCEEDED")
    else:
        print("TESTS FAILED")
        sys.exit(1)

if __name__ == '__main__':
    main(sys.argv[1:])
