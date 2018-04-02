#!/usr/bin/python
import subprocess

def runGetDscLocalConfigurationManager():
    getDscLocalConfigurationManagerCommand = "sudo -u omsagent /opt/microsoft/omsconfig/Scripts/GetDscLocalConfigurationManager.py"
    getDscLocalConfigurationManagerProcess = subprocess.Popen(getDscLocalConfigurationManagerCommand, shell = True)
    getDscLocalConfigurationManagerReturnCode = getDscLocalConfigurationManagerProcess.wait()
    return getDscLocalConfigurationManagerReturnCode

def runPerformRequiredConfigurationChecks():
    performRequiredConfigurationChecksCommand = "sudo -u omsagent /opt/microsoft/omsconfig/Scripts/PerformRequiredConfigurationChecks.py"
    performRequiredConfigurationChecksProcess = subprocess.Popen(performRequiredConfigurationChecksCommand, shell = True)
    performRequiredConfigurationChecksReturnCode = performRequiredConfigurationChecksProcess.wait()
    return performRequiredConfigurationChecksReturnCode

def main():
    getDscLocalConfigurationManagerReturnCode = runGetDscLocalConfigurationManager()
    if (getDscLocalConfigurationManagerReturnCode != 0):
        return getDscLocalConfigurationManagerReturnCode

    performRequiredConfigurationChecksReturnCode = runPerformRequiredConfigurationChecks()
    return performRequiredConfigurationChecksReturnCode

if __name__ == '__main__':
    main()
