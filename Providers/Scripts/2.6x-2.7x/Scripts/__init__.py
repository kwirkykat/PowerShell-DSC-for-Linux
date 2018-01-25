from os import listdir, name
from os.path import join, realpath, split

pythonFileExtension = '.py'

pathToCurrentScript = realpath(__file__)
pathToParentFolder, currentFileName = split(pathToCurrentScript)

scriptsToImport = []

for fileName in listdir(pathToParentFolder):
    if fileName.endswith(pythonFileExtension) and fileName != currentFileName:
        # Remove the file extension
        scriptNameWithoutExtension = fileName[:-len(pythonFileExtension)]
        
        # Add the script to the list of scripts to import
        scriptsToImport.append(scriptNameWithoutExtension)

__all__= scriptsToImport
