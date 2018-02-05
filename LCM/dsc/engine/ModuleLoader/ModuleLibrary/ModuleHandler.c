/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#if defined(_MSC_VER)
#include <sal.h>
#endif

#include <MI.h>
#include "EngineHelper.h"
#include "micodec.h"
#include "ModuleHandler.h"
#include "ModuleHandlerInternal.h"
#include "DSC_Systemcalls.h"
#include "ModuleValidator.h"
#include "EventWrapper.h"

#include "Resources_LCM.h"

extern const ModuleManagerFT g_ModuleManagerFT;


MI_Result MI_CALL InitializeModuleManager( MI_Uint32 flags,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError,
                                          _Outptr_result_maybenull_ ModuleManager **moduleManager)
{
    MI_Result r = MI_RESULT_OK;
    ModuleManager *tempModuleManager = NULL;
    if( moduleManager == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_MODMAN_NULLPARAM);
    }
    SetJobId();

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *moduleManager = NULL;

    tempModuleManager = (ModuleManager *) DSC_malloc( sizeof(ModuleManager), NitsHere());
    if( tempModuleManager == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }

    tempModuleManager->reserved2 = (ptrdiff_t) NULL;
    tempModuleManager->reserved1 = MODULEHANDLER_NOTLOADED;
    tempModuleManager->ft = &g_ModuleManagerFT;
    *moduleManager = tempModuleManager;

    return r;
}

MI_Result MI_CALL LoadModuleManager(_Inout_ ModuleManager *moduleManager,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    if( moduleManager->reserved1 == MODULEHANDLER_LOADED)
    {
        return MI_RESULT_OK;
    }
    else
    {
        MI_Application *miApp = NULL;
        ModuleLoaderObject *moduleLoader = NULL;
        MI_Result r = MI_RESULT_OK;
        /*Create MI_Application object*/
        miApp = (MI_Application *) DSC_malloc( sizeof(MI_Application), NitsHere());
        if( miApp == NULL)
        {
            return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
        }
        memset(miApp,  0, sizeof(MI_Application));
        r = DSC_MI_Application_Initialize(0, NULL, NULL, miApp);
        if( r != MI_RESULT_OK)
        {
            DSC_free(miApp);
            return GetCimMIError(r, extendedError,ID_MODMAN_APPINIT_FAILED);
        }
        r = GetModuleLoader(miApp, &moduleLoader, extendedError);
        if( r != MI_RESULT_OK)
        {
            MI_Application_Close(miApp);
            DSC_free(miApp);
            return r;
        }
        moduleManager->reserved2 = (ptrdiff_t) moduleLoader;
        moduleManager->reserved1 = MODULEHANDLER_LOADED;
        return MI_RESULT_OK;
    }
}


MI_Result MI_CALL ModuleManager_Close(_Inout_ ModuleManager *moduleManager,
                                      _Outptr_opt_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;
    ModuleLoaderObject *moduleLoader = NULL;

    if (extendedError)
    {
        *extendedError = NULL;
    }

    if( moduleManager == NULL ||
        moduleManager->ft == NULL)
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_PARAM_INVALID);
    }

    //Cleanup stuff
    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    if( moduleLoader)
    {
        for( xCount = 0 ; xCount< moduleLoader->schemaCount ; xCount++)
        {
            MI_Class_Delete(moduleLoader->providerSchema[xCount]);
        }
        DSC_free(moduleLoader->providerSchema);

        for( xCount = 0 ; xCount< moduleLoader->regisrationCount; xCount++)
        {
            MI_Instance_Delete(moduleLoader->registrationSchema[xCount]);
        }
        DSC_free(moduleLoader->registrationSchema);
        DSC_free(moduleLoader->schemaToRegistrationMapping);
        MI_OperationOptions_Delete(moduleLoader->options);
        MI_OperationOptions_Delete(moduleLoader->strictOptions);
        MI_Deserializer_Close(moduleLoader->deserializer);
        MI_Application_Close(moduleLoader->application);
        DSC_free(moduleLoader->application);
        DSC_free(moduleLoader->deserializer);
        DSC_free(moduleLoader->options);
        DSC_free(moduleLoader->strictOptions);
        DSC_free(moduleLoader);
    }

    DSC_free(moduleManager);
    return MI_RESULT_OK;
}



MI_Result ModuleManager_LoadInstanceDocument (
    _In_ ModuleManager *moduleManager,
    MI_Uint32 flags,
    _In_count_(documentSize) MI_Uint8 *document,
    _In_ MI_Uint32 documentSize,
    _Outptr_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_InstanceA *resources,
    _Outptr_result_maybenull_ MI_Instance **documentInstance)
{
    MI_Result r = MI_RESULT_OK;
    MI_InstanceA miInstanceArray = {0};
    MI_ClassA miClassArray = {0};
    ModuleLoaderObject *moduleLoader = NULL;


    if( moduleManager == NULL || document == NULL || resources == NULL || documentInstance == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_LOADDOC_NULLPARAM);
    }

    memset(resources, 0, sizeof(MI_InstanceA));
    *documentInstance = NULL;

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    miClassArray.size = moduleLoader->schemaCount;
    miClassArray.data = moduleLoader->providerSchema;

    r = GetInstanceFromBuffer( moduleManager, moduleLoader->application, moduleLoader->deserializer, moduleLoader->options, &miClassArray, document, documentSize, &miInstanceArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }
    /*FilterForConfigurationResource will cleanup as needed.*/
    r = FilterForConfigurationResource(&miInstanceArray, resources, documentInstance, extendedError);
    return r;


}

MI_Result ModuleManager_LoadInstanceDocumentFromLocation (
    _In_ ModuleManager *moduleManager,
    MI_Uint32 flags,
    _In_z_  const MI_Char *documentLocation,
    _Outptr_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_InstanceA *resources,
    _Outptr_result_maybenull_ MI_Instance **documentInstance)
{
    MI_Result r = MI_RESULT_OK;
    MI_InstanceA miInstanceArray = {0};
    MI_ClassA miClassArray = {0};
    ModuleLoaderObject *moduleLoader = NULL;
    DSC_EventWriteMessageLoadingInstance(documentLocation);

    if( moduleManager == NULL || documentLocation == NULL || documentInstance == NULL || resources == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_LOADDOC_NULLPARAM);
    }
    memset(resources, 0, sizeof(MI_InstanceA));

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }


    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    miClassArray.size = moduleLoader->schemaCount;
    miClassArray.data = moduleLoader->providerSchema;

    r = GetInstanceFromSingleMOF( moduleManager, flags | VALIDATE_DOCUMENT_INSTANCE,
                moduleLoader->application, moduleLoader->deserializer,
                moduleLoader->options, moduleLoader->strictOptions, &miClassArray,
                documentLocation, &miInstanceArray, extendedError);

    if( r != MI_RESULT_OK)
    {
        return r;
    }
    r = FilterForConfigurationResource(&miInstanceArray, resources, documentInstance,extendedError);

    return r;
}


MI_Result  ModuleManager_GetRegistrationInstance (
    _In_ ModuleManager *moduleManager,
    _In_z_ const MI_Char *className,
    _Outptr_result_maybenull_ const MI_Instance **registrationInstance,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;
    MI_Result r = MI_RESULT_OK;
    ModuleLoaderObject *moduleLoader = NULL;
    if( moduleManager == NULL || className == NULL || registrationInstance == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_GETREG_NULLPARAM);
    }

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *registrationInstance = NULL;
    //special case for meta configuration where we don't need the registration
    if(Tcscasecmp(className, METACONFIG_CLASSNAME) == 0)
    {
        return r;
    }

    for( xCount = 0 ; xCount < moduleLoader->schemaCount; xCount++)
    {
        if( Tcscasecmp(className, moduleLoader->providerSchema[xCount]->classDecl->name) == 0 )
        {
            if( moduleLoader->schemaToRegistrationMapping[xCount] == (MI_Uint32)-1 ||
                moduleLoader->schemaToRegistrationMapping[xCount] > moduleLoader->regisrationCount)
            {
                return GetCimMIError(MI_RESULT_NOT_FOUND, extendedError,ID_MODMAN_REGINS_NOTFOUND);
            }
            *registrationInstance = moduleLoader->registrationSchema[ moduleLoader->schemaToRegistrationMapping[xCount] ] ;
            return MI_RESULT_OK;
        }
    }
    /*If here we didn't find the registration*/
    return GetCimMIError(MI_RESULT_NOT_FOUND, extendedError,ID_MODMAN_CONFIGCLASS_NOTREG);

}

/*Callers responsibility to fill Namespace if needed.*/

_Return_type_success_(return == MI_RESULT_OK)
    MI_Result ModuleManager_GetProviderCompatibleInstance (
    _In_ ModuleManager *moduleManager,
    _In_ MI_Instance *inInstance,
    _Outptr_result_maybenull_ MI_Instance **outInstance,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    ModuleLoaderObject *moduleLoader = NULL;
    MI_Instance * filteredInstance = NULL;

    if( moduleManager == NULL || inInstance == NULL || outInstance == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_GETCOMPAT_NULLPARAM);
    }

    *outInstance = NULL;

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }
    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    // Remove non-provider properties.
    r = GetFilteredResource(moduleLoader->application ,inInstance, &filteredInstance, extendedError);
    if( r != MI_RESULT_OK)
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_GETFILTERED_FAILED);
    }
    *outInstance = filteredInstance;
    return r;
}

MI_Result ModuleManager_Update (
    _In_ ModuleManager *moduleManager,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0;
    MI_Application *miApp = NULL;
    ModuleLoaderObject *inModuleLoader = NULL;
    ModuleLoaderObject *outModuleLoader = NULL;

    if( moduleManager == NULL ||
        moduleManager->ft == NULL  || NitsShouldFault(NitsHere(), NitsAutomatic) )
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_PARAM_INVALID);
    }
    inModuleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    if( inModuleLoader == NULL)
    {
        // create application object.
        miApp = (MI_Application *) DSC_malloc( sizeof(MI_Application), NitsHere());
        if( miApp == NULL)
        {
            return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
        }
        memset(miApp,  0, sizeof(MI_Application));
        r = DSC_MI_Application_Initialize(0, NULL, NULL, miApp );
        if( r != MI_RESULT_OK)
        {
            DSC_free(miApp);
            return GetCimMIError(r, extendedError,ID_MODMAN_APPINIT_FAILED);
        }
    }
    else
    {
        miApp = inModuleLoader->application;
    }
    /*First get new registration information. If we fail, user can still use old data.*/
    r = GetModuleLoader(miApp, &outModuleLoader, extendedError);
    if( r != MI_RESULT_OK)
    {
        if( inModuleLoader == NULL)
        {
            MI_Application_Close(miApp);
            DSC_free(miApp);
        }
        return r;
    }

    if(inModuleLoader)
    {
        //Cleanup stuff
        for( xCount = 0 ; xCount< inModuleLoader->schemaCount ; xCount++)
        {
            MI_Class_Delete(inModuleLoader->providerSchema[xCount]);
        }
        DSC_free(inModuleLoader->providerSchema);

        for( xCount = 0 ; xCount< inModuleLoader->regisrationCount; xCount++)
        {
            MI_Instance_Delete(inModuleLoader->registrationSchema[xCount]);
        }
        DSC_free(inModuleLoader->registrationSchema);
        DSC_free(inModuleLoader->schemaToRegistrationMapping);
        DSC_free(inModuleLoader);
    }

    moduleManager->reserved2 = (ptrdiff_t) outModuleLoader;

    return MI_RESULT_OK;

}


MI_Result GetModuleLoader( _In_ MI_Application *miApp,
                          _Out_ ModuleLoaderObject **moduleLoader,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_ClassA miClassArray = {0};
    MI_InstanceA miInstanceArray = {0};
    MI_Deserializer *de;
    MI_OperationOptions *options;
    MI_OperationOptions *strictOptions;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    r = GetMofDeserializer(miApp, &de, &options, &strictOptions, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    /*Get the schema from MOFs*/
    r = GetSchemaFromMOFs(miApp, de, options, &miClassArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        MI_Deserializer_Close(de);
        MI_OperationOptions_Delete(options);
        DSC_free(de);
        DSC_free(options);
        CleanUpClassCache(&miClassArray);
        return r;
    }

    /*Get the Registration information from MOFs*/
    r = GetRegistrationInstanceFromMOFs(NULL, miApp, de, options, strictOptions, &miClassArray, &miInstanceArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        MI_Deserializer_Close(de);
        MI_OperationOptions_Delete(options);
        DSC_free(de);
        DSC_free(options);
        CleanUpClassCache(&miClassArray);
        CleanUpInstanceCache(&miInstanceArray);
        return r;
    }

    /*Perform registration against schema validation*/
    r = ValidateProviderRegistrationAgainstSchema(&miClassArray, &miInstanceArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        MI_Deserializer_Close(de);
        MI_OperationOptions_Delete(options);
        DSC_free(de);
        DSC_free(options);
        CleanUpClassCache(&miClassArray);
        CleanUpInstanceCache(&miInstanceArray);
        return r;
    }

    /*Form mapping tables*/

    r = GetMappingTable(miApp, &miClassArray, &miInstanceArray, moduleLoader, extendedError);
    if( r != MI_RESULT_OK)
    {
        MI_Deserializer_Close(de);
        MI_OperationOptions_Delete(options);
        DSC_free(de);
        DSC_free(options);
        CleanUpClassCache(&miClassArray);
        CleanUpInstanceCache(&miInstanceArray);
        return r;
    }

    (*moduleLoader)->deserializer = de;
    (*moduleLoader)->options = options;
    (*moduleLoader)->strictOptions = strictOptions;
    return r;
}

/*caller will cleanup miClassArray*/
MI_Result GetCoreSchema(_In_ MI_Application *miApp,
                        _In_ MI_Deserializer *deserializer,
                        _In_ MI_OperationOptions * options,
                        _Inout_ MI_ClassA *miClassArray,
                        _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return GetSystemSchema(miApp, deserializer, options, BASESCHEMA_FILENAME, NULL, miClassArray, extendedError);
}

MI_Result GetMetaConfigSchema(_In_ MI_Application *miApp,
                              _In_ MI_Deserializer *deserializer,
                              _In_ MI_OperationOptions * options,
                              _Inout_ MI_ClassA *miClassArray,
                              _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    r = GetCoreSchema(miApp, deserializer, options, miClassArray, extendedError);
    if(r != MI_RESULT_OK)
    {
        return r;
    }
    return GetSystemSchema(miApp, deserializer, options, METACONFIGSCHEMA_FILENAME, miClassArray, miClassArray, extendedError);
}

MI_Result GetMappingTable(_In_ MI_Application *miApp,
                          _In_ MI_ClassA *miClassArray,
                          _In_ MI_InstanceA *miInstanceArray,
                          _Out_ ModuleLoaderObject **moduleLoader,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0, yCount = 0;
    MI_Result r = MI_RESULT_OK;
    MI_Value className;
    MI_Session miSession = MI_SESSION_NULL;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    /*Allocate structures*/
    *moduleLoader = (ModuleLoaderObject *)DSC_malloc(sizeof(ModuleLoaderObject), NitsHere());
    if( *moduleLoader == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }
    (*moduleLoader)->schemaToRegistrationMapping = (MI_Uint32 *) DSC_malloc(sizeof(MI_Uint32) * miClassArray->size, NitsHere());
    if( (*moduleLoader)->schemaToRegistrationMapping == NULL)
    {
        DSC_free(*moduleLoader);
        *moduleLoader = NULL;
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }

    memset((*moduleLoader)->schemaToRegistrationMapping, -1, sizeof(MI_Uint32) * miClassArray->size );

    r = DSC_MI_Application_NewSession(miApp, NULL, NULL, NULL, NULL, NULL, &miSession);
    if( r != MI_RESULT_OK )
    {
        DSC_free(*moduleLoader);
        *moduleLoader = NULL;
        return GetCimMIError(r, extendedError, ID_CAINFRA_NEWSESSION_FAILED);
    }

    /* Create Mapping*/
    for( xCount = 0; xCount < miClassArray->size ; xCount++)
    {
        for( yCount = 0; yCount < miInstanceArray->size ; yCount++)
        {
            r = DSC_MI_Instance_GetElement(miInstanceArray->data[yCount], MI_T("className"), &className, NULL, NULL, NULL);
            if( r != MI_RESULT_OK )
            {
                DSC_free(*moduleLoader);
                *moduleLoader = NULL;
                MI_Session_Close(&miSession, NULL, NULL);
                return GetCimMIError(r, extendedError, ID_MODMAN_MAPPING_CLASSNAME_NOTFOUND);
            }
            if( Tcscasecmp( miClassArray->data[xCount]->classDecl->name , className.string) == 0 )
            {
                // disable validation for non-windows for now. Add it back once OMI team supports getting full RTTI in binary protocol.
#if defined(_MSC_VER)
                // Validate the mapping and provider registration
                r = ValidateDSCProviderMapping(miInstanceArray->data[yCount], miClassArray->data[xCount], &miSession, extendedError);
                if( r != MI_RESULT_OK)
                {
                    DSC_free(*moduleLoader);
                    *moduleLoader = NULL;
                    MI_Session_Close(&miSession, NULL, NULL);
                    return r;
                }
#endif
                ((*moduleLoader)->schemaToRegistrationMapping)[xCount] = yCount;
                break;
            }
        }
    }

    MI_Session_Close(&miSession, NULL, NULL);

    /*Fill structures*/
    (*moduleLoader)->application = miApp;
    (*moduleLoader)->providerSchema = miClassArray->data;
    (*moduleLoader)->schemaCount = miClassArray->size;
    (*moduleLoader)->registrationSchema = miInstanceArray->data;
    (*moduleLoader)->regisrationCount = miInstanceArray->size;
    return MI_RESULT_OK;
}

MI_Result GetFilteredResource( _In_ MI_Application *miApp,
                              _In_ MI_Instance *inInstance,
                              _Outptr_result_maybenull_ MI_Instance **outInstance,
                              _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0, yCount = 0;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;
    if( miApp == NULL || inInstance == NULL || outInstance == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_FILTER_ARGNULL);
    }

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *outInstance = NULL;

    r = DSC_MI_Application_NewInstance(miApp, inInstance->classDecl->name, NULL, outInstance);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError,ID_CAINFRA_GET_NEWAPPLICATIONINSTANCE_FAILED);
    }

    /*Filter properties*/
    for( xCount = 0 ; xCount < inInstance->classDecl->numProperties ; xCount++)
    {
        for (yCount = 0; g_BaseResourceConfiguration[yCount].wszPropName != NULL; yCount++)
        {
            if( Tcscasecmp(inInstance->classDecl->properties[xCount]->name, g_BaseResourceConfiguration[yCount].wszPropName) == 0 )
            {
                break;
            }
        }
        if( g_BaseResourceConfiguration[yCount].wszPropName == NULL)
        {
            r = DSC_MI_Instance_GetElement(inInstance, inInstance->classDecl->properties[xCount]->name,
                &value, &type, &flags, NULL);
            if( r != MI_RESULT_OK )
            {
                MI_Instance_Delete(*outInstance);
                *outInstance = NULL;
                return GetCimMIError(r, extendedError,ID_MODMAN_GETELEMENT_FAILED);
            }
            // Not base resource property, add it
            r = DSC_MI_Instance_AddElement(*outInstance, inInstance->classDecl->properties[xCount]->name,
                &value, type, flags);
            if( r != MI_RESULT_OK)
            {
                *outInstance = NULL;
                return GetCimMIError(r, extendedError,ID_MODMAN_GETELEMENT_FAILED);
            }

        }
    }
    return r;

}

MI_Result GetInstanceFromBuffer(_In_opt_ ModuleManager *moduleManager,
                                _In_ MI_Application *miApp,
                                _In_ MI_Deserializer *deserializer,
                                _In_ MI_OperationOptions * options,
                                _In_ MI_ClassA *classArray,
                                _In_count_(instanceBufferSize) MI_Uint8 *instanceBuffer,
                                _In_ MI_Uint32 instanceBufferSize,
                                _Inout_ MI_InstanceA *miInstanceArray,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_InstanceA *miTempInstanceArray = NULL;
    MI_Uint32 readBytes;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    r = MI_Deserializer_DeserializeInstanceArray(deserializer, 0, options, 0, instanceBuffer, instanceBufferSize, classArray, &readBytes, &miTempInstanceArray, extendedError);
    if( r != MI_RESULT_OK || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        CleanUpDeserializerInstanceCache(miTempInstanceArray);
        return r;
    }
    /*Update actual cache*/
    r = UpdateInstanceArray(miTempInstanceArray, miInstanceArray, extendedError, MI_TRUE);
    if( r != MI_RESULT_OK )
    {
        CleanUpDeserializerInstanceCache(miTempInstanceArray);
    }
    return r;
}

MI_Result GetInstanceFromSingleMOF(_In_opt_ ModuleManager *moduleManager,
                                   _In_ MI_Uint32 flags,
                                   _In_ MI_Application *miApp,
                                   _In_ MI_Deserializer *deserializer,
                                   _In_ MI_OperationOptions * options,
                                   _In_ MI_OperationOptions * strictOptions,
                                   _In_ MI_ClassA *classArray,
                                   _In_z_ const MI_Char *mofModuleFilePath,
                                   _Inout_ MI_InstanceA *miInstanceArray,
                                   _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    /*Form full path to mof file*/
    MI_InstanceA *miTempInstanceArray = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 contentSize;
    MI_Uint32 readBytes;
    MI_ClassA miClassArray = {0};

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    r = ReadFileContent(mofModuleFilePath, &pbuffer, &contentSize, extendedError);
    if(r != MI_RESULT_OK)
    {
        return r;
    }
    miClassArray.size = classArray->size;
    miClassArray.data = classArray->data;
// We will discover PS schema only if we are running in windows.

#if defined(_MSC_VER)

    r = MI_Deserializer_DeserializeInstanceArray(deserializer, 0, options, 0, pbuffer, contentSize, &miClassArray, &readBytes, &miTempInstanceArray, extendedError);

    if( r != MI_RESULT_OK )
    {
        DSC_free(pbuffer);
        return r;
    }
    if( moduleManager)
    {
        MI_Result innerResult = MI_RESULT_OK;
        MI_Uint32 xCount = 0, classCount = 0, yCount = 0;
        MI_Value value;
        MI_Uint32 valueFlags;
        for( xCount = 0 ; xCount < miTempInstanceArray->size ; xCount++)
        {
            for( yCount = 0 ; yCount < classArray->size ; yCount++)
            {
                if( Tcscasecmp(miTempInstanceArray->data[xCount]->classDecl->name, classArray->data[yCount]->classDecl->name) == 0 )
                {
                    break;
                }
            }
            if(classArray->size == yCount)
            {
                classCount++;
            }
        }

        // There could be schema not loaded yet
        if( classCount > 0 )
        {
            MI_StringA classNames = {0};
            MI_StringA moduleNames = {0};
            MI_StringA moduleVersions = {0};
            classNames.size = classCount;
            classNames.data = (MI_Char**) DSC_malloc( sizeof(MI_Char*) * classCount, TLINE);
            if( classNames.data == NULL)
            {
                 DSC_free(pbuffer);
                CleanUpDeserializerInstanceCache(miTempInstanceArray);
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
            }
            moduleNames.size = classCount;
            moduleNames.data = (MI_Char**) DSC_malloc( sizeof(MI_Char*) * classCount, TLINE);
            if( moduleNames.data == NULL)
            {
                 DSC_free(pbuffer);
                 DSC_free(classNames.data);
                CleanUpDeserializerInstanceCache(miTempInstanceArray);
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
            }
            moduleVersions.size = classCount;
            moduleVersions.data = (MI_Char**) DSC_malloc( sizeof(MI_Char*) * classCount, TLINE);
            if( moduleVersions.data == NULL)
            {
                 DSC_free(pbuffer);
                 DSC_free(classNames.data);
                 DSC_free(moduleNames.data);
                CleanUpDeserializerInstanceCache(miTempInstanceArray);
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
            }
            memset(moduleVersions.data, 0, sizeof(MI_Char*) * classCount);
            for( xCount = 0, classCount = 0; xCount < miTempInstanceArray->size ; xCount++)
            {
                for( yCount = 0 ; yCount < classArray->size ; yCount++)
                {
                    if( Tcscasecmp(miTempInstanceArray->data[xCount]->classDecl->name, classArray->data[yCount]->classDecl->name) == 0 )
                    {
                        break;
                    }
                }
                if(classArray->size == yCount)
                {
                    classNames.data[classCount] = (MI_Char*)miTempInstanceArray->data[xCount]->classDecl->name;
                    /*Get module Name and send it.*/
                    innerResult = MI_Instance_GetElement(miTempInstanceArray->data[xCount], OMI_BaseResource_ModuleName , &value, NULL, &valueFlags, NULL);
                    if( innerResult == MI_RESULT_OK && !(valueFlags & MI_FLAG_NULL) && value.string != NULL)
                    {
                        moduleNames.data[classCount] = value.string;
                    }
                    else
                    {
                        // if module name is not specified, we assume class name as module name.
                        moduleNames.data[classCount] = (MI_Char*)miTempInstanceArray->data[xCount]->classDecl->name;
                    }

                    /*Get module version and send it.*/
                    innerResult = MI_Instance_GetElement(miTempInstanceArray->data[xCount], OMI_BaseResource_ModuleVersion , &value, NULL, &valueFlags, NULL);
                    if( innerResult == MI_RESULT_OK && !(valueFlags & MI_FLAG_NULL) && value.string != NULL)
                    {
                        moduleVersions.data[classCount] = value.string;
                    }
                    classCount++;
                }
            }
            r = UpdateAndReloadInMemoryCache(moduleManager, &classNames, &moduleNames, &moduleVersions, extendedError);
            DSC_free(classNames.data);
            DSC_free(moduleNames.data);
            DSC_free(moduleVersions.data);
            CleanUpDeserializerInstanceCache(miTempInstanceArray);
            if( r != MI_RESULT_OK)
            {
                 DSC_free(pbuffer);
                return r;
            }
            {
                    ModuleLoaderObject *moduleLoader = NULL;
                //call the method again with strict to enforce schema validation
                moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
                miClassArray.size = moduleLoader->schemaCount;
                miClassArray.data = moduleLoader->providerSchema;
            }
        }
    }
    else
    {
        CleanUpDeserializerInstanceCache(miTempInstanceArray);
    }
#endif

    miTempInstanceArray = NULL;

    r = MI_Deserializer_DeserializeInstanceArray(deserializer, 0, strictOptions, 0, pbuffer, contentSize, &miClassArray, &readBytes, &miTempInstanceArray, extendedError);

    if( r != MI_RESULT_OK )
    {
        DSC_free(pbuffer);
        return r;
    }

    if(pbuffer)
    {
        DSC_free(pbuffer);
        pbuffer = NULL;
    }



    if( flags & VALIDATE_REGISTRATION_INSTANCE)
    {
        /*Validate Registration Instance*/
        r = ValidateDSCProviderRegistrationInstance(miTempInstanceArray, extendedError);
        if( r != MI_RESULT_OK)
        {
            CleanUpDeserializerInstanceCache(miTempInstanceArray);
            return r;
        }
    }
    else if( flags & VALIDATE_DOCUMENT_INSTANCE )
    {
        /*Validate mof instance*/
        r = ValidateDSCDocumentInstance(miTempInstanceArray, flags, extendedError);
        if( r != MI_RESULT_OK)
        {
            CleanUpDeserializerInstanceCache(miTempInstanceArray);
            return r;
        }
    }
    /*Update actual cache*/
    r = UpdateInstanceArray(miTempInstanceArray, miInstanceArray, extendedError, MI_TRUE);
    if( r != MI_RESULT_OK )
    {
        CleanUpDeserializerInstanceCache(miTempInstanceArray);
    }
    return r;
}

MI_Result MI_CALL SchemaCallback(_In_opt_ void *context,
                                 _In_opt_z_ const MI_Char *serverName,
                                 _In_opt_z_ const MI_Char *namespaceName,
                                 _In_z_ const MI_Char *className,
                                 _Outptr_ MI_Class **requestedClassObject)
{
    MI_ClassA *classContainer = NULL;
    MI_Uint32 iCount = 0;
    if( context == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    classContainer = (MI_ClassA*)context;
    for( iCount = 0 ; iCount < classContainer->size; iCount++)
    {
        if(Tcscasecmp(className , classContainer->data[iCount]->classDecl->name) == 0 )
        {
            return MI_Class_Clone(classContainer->data[iCount], requestedClassObject);
        }
    }
    return MI_RESULT_NOT_FOUND;
}


/*Cleanup is done by this method. Caller should not cleanup in success or failure case*/
MI_Result FilterForConfigurationResource(_Inout_ MI_InstanceA *inputInstanceArray,
                                         _Inout_ MI_InstanceA *outputInstanceArray,
                                         _Outptr_result_maybenull_ MI_Instance **documentInstance,
                                         _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0, yCount = 0;
    MI_Uint32 flags = 0;
    MI_Uint32 resourceCount = 0;
    MI_Uint8 *embeddedResourceMap = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_Instance **tempOutput = NULL;
    MI_Boolean bDocumentInstance = MI_FALSE;
 
    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *documentInstance = NULL;

    //if there are embedded resource we won't copy them to inputInstanceArray so need to release them ourselves
    embeddedResourceMap = (MI_Uint8 *)DSC_malloc( inputInstanceArray->size * sizeof(MI_Uint8), NitsHere());
    if( embeddedResourceMap == NULL)
    {
        CleanUpInstanceCache(inputInstanceArray);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }

    for(xCount = 0 ; xCount < inputInstanceArray->size ; xCount++)
    {
        embeddedResourceMap[xCount] = 0;

        if( Tcscasecmp(inputInstanceArray->data[xCount]->classDecl->name, BASE_DOCUMENT_CLASSNAME) == 0 )
        {
            if( bDocumentInstance )
            {
                //Error multiple instances specified, only 1 allowed
                CleanUpInstanceCache(inputInstanceArray);
                DSC_free(embeddedResourceMap);
                return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_FILTER_MULTIPLEINS);
            }
            else
            {
                *documentInstance = inputInstanceArray->data[xCount];
                bDocumentInstance = MI_TRUE;
                embeddedResourceMap[xCount] = 2;
            }
        }
        //we don't check resourceid if it's other embeded instances
        else if ((inputInstanceArray->data[xCount]->classDecl->superClass != NULL && Tcscasecmp(inputInstanceArray->data[xCount]->classDecl->superClass, BASE_RESOURCE_CLASSNAME) == 0) ||
                 Tcscasecmp(inputInstanceArray->data[xCount]->classDecl->name, METACONFIG_CLASSNAME) == 0)
        {
            resourceCount++;

            // Resource must contain resourceID as mandatory parameter.
            if(inputInstanceArray->data[xCount]->classDecl->superClass != NULL && Tcscasecmp(inputInstanceArray->data[xCount]->classDecl->superClass, BASE_RESOURCE_CLASSNAME) == 0 )
            {
                r = DSC_MI_Instance_GetElement(inputInstanceArray->data[xCount], OMI_BaseResource_ResourceId, NULL, NULL, &flags, NULL);
                if( r != MI_RESULT_OK || (flags & MI_FLAG_NULL))
                {
                    CleanUpInstanceCache(inputInstanceArray);
                    DSC_free(embeddedResourceMap);
                    return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_FILTER_RESOURCEID);
                }
            }
            embeddedResourceMap[xCount] = 1;
        }
    }

    if( bDocumentInstance == MI_FALSE || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        //mandatory Document instance not specified.
        CleanUpInstanceCache(inputInstanceArray);
        DSC_free(embeddedResourceMap);
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_FILTER_NOINSTANCE);

    }
    tempOutput = (MI_Instance **)DSC_malloc( resourceCount * sizeof(MI_Instance*), NitsHere());
    if( tempOutput == NULL)
    {
        CleanUpInstanceCache(inputInstanceArray);
        DSC_free(embeddedResourceMap);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }

    for(xCount = 0 ; xCount < inputInstanceArray->size ; xCount++)
    {
        if(embeddedResourceMap[xCount] == 1)
        {
            tempOutput[yCount++] = inputInstanceArray->data[xCount];
        }
        else if (embeddedResourceMap[xCount] == 0)
        {
            MI_Instance_Delete(inputInstanceArray->data[xCount]);
        }
    }
    outputInstanceArray->size = resourceCount;
    outputInstanceArray->data = tempOutput;
    DSC_free(inputInstanceArray->data);
    DSC_free(embeddedResourceMap);
    return r;
}


MI_Result GetMofDeserializer(_In_ MI_Application *miApp,
                             _Outptr_result_maybenull_ MI_Deserializer **deserializer,
                             _Outptr_result_maybenull_ MI_OperationOptions **operationOptions,
                             _Outptr_result_maybenull_ MI_OperationOptions **strictOperationOptions,
                             _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *operationOptions = NULL;

    *deserializer = (MI_Deserializer*) DSC_malloc(sizeof(MI_Deserializer), NitsHere());
    if(*deserializer == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    memset(*deserializer, 0, sizeof(MI_Deserializer));

    *operationOptions = (MI_OperationOptions*) DSC_malloc(sizeof(MI_OperationOptions), NitsHere());
    if(*operationOptions == NULL)
    {
        DSC_free(*deserializer);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    memset(*operationOptions, 0, sizeof(MI_OperationOptions));

    r = DSC_MI_Application_NewOperationOptions(miApp, MI_FALSE, *operationOptions);
    if (r!=MI_RESULT_OK)
    {
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        return GetCimMIError(r, extendedError, ID_MODMAN_NEWOO_FAILED);
    }

    r = DSC_MI_OperationOptions_SetString(*operationOptions, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME, MOFCODEC_SCHEMA_VALIDATION_IGNORE, 0);
    if (r!=MI_RESULT_OK )
    {
        MI_OperationOptions_Delete(*operationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
       return GetCimMIError(r, extendedError, ID_MODMAN_OOSET_FAILED);
    }

    *strictOperationOptions = (MI_OperationOptions*) DSC_malloc(sizeof(MI_OperationOptions), NitsHere());
    if(*strictOperationOptions == NULL)
    {
        MI_OperationOptions_Delete(*operationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    memset(*strictOperationOptions, 0, sizeof(MI_OperationOptions));

    r = DSC_MI_Application_NewOperationOptions(miApp, MI_FALSE, *strictOperationOptions);
    if (r!=MI_RESULT_OK)
    {
        MI_OperationOptions_Delete(*operationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        DSC_free(*strictOperationOptions);
        return GetCimMIError(r, extendedError, ID_MODMAN_NEWOO_FAILED);
    }

    r = DSC_MI_OperationOptions_SetString(*strictOperationOptions, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME, MOFCODEC_SCHEMA_VALIDATION_STRICT, 0);
    if (r!=MI_RESULT_OK )
    {
        MI_OperationOptions_Delete(*operationOptions);
        MI_OperationOptions_Delete(*strictOperationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        DSC_free(*strictOperationOptions);
       return GetCimMIError(r, extendedError, ID_MODMAN_OOSET_FAILED);
    }

    r = DSC_MI_Application_NewDeserializer_Mof(miApp, 0, MOFCODEC_FORMAT, *deserializer);
    if (r!=MI_RESULT_OK)
    {
        MI_OperationOptions_Delete(*operationOptions);
        MI_OperationOptions_Delete(*strictOperationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        DSC_free(*strictOperationOptions);
        return GetCimMIError(r, extendedError, ID_LCMHELPER_DESERIALIZER_CREATE_FAILED);
    }

    return MI_RESULT_OK;
}

/*caller will cleanup miClassArray*/
MI_Result GetSystemSchema(_In_ MI_Application *miApp,
                          _In_ MI_Deserializer *deserializer,
                          _In_ MI_OperationOptions * options,
                          _In_z_ const MI_Char* schemaName,
                          _In_opt_ MI_ClassA *inputClasses,
                          _Inout_ MI_ClassA *miClassArray,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Char *envResolvedPath = NULL;
    MI_Char *filePath = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_ClassA * miTempClassArray = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 contentSize;
    MI_Uint32 readBytes;

    if( miClassArray == NULL || miApp == NULL  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_SYSTEMCACHE_INVALIDPARAM);
    }

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    /* Resolve schema search path*/
    r = ResolvePath(&envResolvedPath, &filePath, GetCoreSchemaPath(), schemaName, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    if( envResolvedPath)
    {
        DSC_free(envResolvedPath);
    }

    r = ReadFileContent(filePath, &pbuffer, &contentSize, extendedError);
    if(r != MI_RESULT_OK )
    {
        return r;
    }

    r = MI_Deserializer_DeserializeClassArray(deserializer, 0, options, 0, pbuffer, contentSize, inputClasses, NULL, NULL, &readBytes, &miTempClassArray, extendedError);

    if( filePath)
    {
        DSC_free(filePath);
    }

    if(pbuffer)
    {
        DSC_free(pbuffer);
    }

    if( r != MI_RESULT_OK || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        CleanUpDeserializerClassCache(miTempClassArray);
        if( r == MI_RESULT_OK)
        {
            r = MI_RESULT_FAILED;
        }
        return r;
    }


    /*Validate Schema*/

    r = ValidateInfrastructureSchema(miTempClassArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        CleanUpDeserializerClassCache(miTempClassArray);
        return r;
    }


    /*Update actual cache*/
    r = UpdateClassArray(miTempClassArray, miClassArray, extendedError, MI_TRUE);
    if( r != MI_RESULT_OK )
    {
        CleanUpDeserializerClassCache(miTempClassArray);
    }
    return r;
}

MI_Result GetSchemaFromSingleMOF(_In_ MI_Application *miApp,
                                 _In_ MI_Deserializer *deserializer,
                                 _In_ MI_OperationOptions * options,
                                 _In_z_ MI_Char *mofModulePath,
                                 _In_z_ MI_Char *schemaFileName,
                                 _Inout_ MI_ClassA *miClassArray,
                                 _In_opt_ MI_ClassA *miDiscoverdSchema,
                                 _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    int result = 0;
    /*Form full path to mof file*/
    MI_Char *fullPath = NULL;
    MI_ClassA *miTempClassArray = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 contentSize;
    MI_Uint32 readBytes;
    size_t fullPathLength = Tcslen(mofModulePath) + 1 + Tcslen(schemaFileName) + 1; // mofModulePath\schemaFileName
    MI_DeserializerCallbacks cb;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    fullPath = (MI_Char*)DSC_malloc(fullPathLength* sizeof(MI_Char), NitsHere());
    if( fullPath == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }
#if defined(_MSC_VER)
    result = Stprintf(fullPath, fullPathLength, MI_T("%T\\%T"), mofModulePath, schemaFileName);
#else
    result = Stprintf(fullPath, fullPathLength, MI_T("%T/%T"), mofModulePath, schemaFileName);
#endif

    if( result <= 0|| NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }

    r = ReadFileContent(fullPath, &pbuffer, &contentSize, extendedError);
    if(r != MI_RESULT_OK)
    {
        return r;
    }

    memset(&cb, 0, sizeof(cb));
    if(miDiscoverdSchema)
    {
        cb.classObjectNeededContext = miDiscoverdSchema;
    }
    else
    {
        cb.classObjectNeededContext = miClassArray;
    }

    cb.classObjectNeeded = SchemaCallback;
    r = MI_Deserializer_DeserializeClassArray(deserializer, 0, options, &cb, pbuffer, contentSize, NULL, NULL, NULL, &readBytes, &miTempClassArray, extendedError);
    DSC_free(fullPath);
    DSC_free(pbuffer);
    if( r != MI_RESULT_OK || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        CleanUpDeserializerClassCache(miTempClassArray);
        if(r == MI_RESULT_OK)           //nits faulted; return MI_RESULT_FAILED
        {
            r = MI_RESULT_FAILED;
        }
        return r;
    }

    /*Validate Schema*/

    r = ValidateDSCProviderSchema(miTempClassArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        CleanUpDeserializerClassCache(miTempClassArray);
        return r;
    }


    /*Update actual cache*/
    r = UpdateClassArray(miTempClassArray, miClassArray, extendedError, MI_TRUE);
    if( r != MI_RESULT_OK )
    {
        CleanUpDeserializerClassCache(miTempClassArray);
    }
    return r;

}

/*Caller will free up miInstanceArray*/
MI_Result GetRegistrationInstanceFromMOFs(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _Inout_ MI_InstanceA *miInstanceArray,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char **pathsForRegistration;
    MI_Uint32 count=0;
    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.
    pathsForRegistration = (MI_Char**)DSC_malloc(NUM_PATHS_TO_LOOK_FOR_PROVIDERS * sizeof(MI_Char*), NitsHere());
    if( pathsForRegistration == NULL)
    {
        return MI_RESULT_FAILED;
    }
    pathsForRegistration[0] = (MI_Char*)GetRegistrationInstanceSearchPath();
    pathsForRegistration[1] = (MI_Char*)GetRegistrationInstanceSearchPathProgFiles();
    for (count = 0; count < NUM_PATHS_TO_LOOK_FOR_PROVIDERS; count++)
    {
        r= GetEachRegistrationInfo(moduleManager,miApp,deserializer,options,strictOptions,classArray,miInstanceArray, extendedError,pathsForRegistration[count]);
        if(r != MI_RESULT_OK)
        {
            DSC_free(pathsForRegistration);
            return r;
        }
    }
    DSC_free(pathsForRegistration);
    return r;
}

MI_Result GetEachRegistrationInfo(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _Inout_ MI_InstanceA *miInstanceArray,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError,
                                          _In_z_ const MI_Char * registrationPath)
{
    Internal_Dir *dirHandle = NULL;
    Internal_DirEnt *dirEntry = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_Char *envResolvedPath = NULL;

    /* Resolve schema search path*/
    r = ResolvePath(&envResolvedPath, NULL, registrationPath, NULL, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    /*Do actual search using search path*/

    dirHandle = Internal_Dir_Open(envResolvedPath, NitsHere() );
    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(envResolvedPath);
        if( dirHandle != NULL )
            Internal_Dir_Close( dirHandle);

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
    }
    dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    while( dirEntry != NULL )
    {
        /* Only process directories as modules are expected to have a directory per module.*/
        if( dirEntry->isDir &&
            (Tcscasecmp(MI_T(".."), dirEntry->name)!=0) &&
            (Tcscasecmp(MI_T("."), dirEntry->name)!=0))
        {
            r = UpdateRegistrationInstanceCache(moduleManager, miApp, deserializer, options, strictOptions, classArray, envResolvedPath, dirEntry->name, miInstanceArray, extendedError);
            if( r != MI_RESULT_OK)
            {
                DSC_free(envResolvedPath);
                Internal_Dir_Close( dirHandle);
                return r;
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    }

    /*Cleanup*/
    Internal_Dir_Close( dirHandle);
    DSC_free(envResolvedPath);
    return MI_RESULT_OK;
}

/*caller will cleanup miClassArray*/
MI_Result GetSchemaFromMOFs(_In_ MI_Application *miApp,
                            _In_ MI_Deserializer *deserializer,
                            _In_ MI_OperationOptions * options,
                            _Inout_ MI_ClassA *miClassArray,
                            _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 count=0;
    MI_Char *envResolvedPath = NULL;
    MI_Char **pathsForSchemas;

    if( miClassArray == NULL || miApp == NULL  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_SCHEMAFROMMOF_INVALIDPARAM);
    }

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    /*Get DSC core schema first*/
    r = GetCoreSchema(miApp, deserializer, options, miClassArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    /* Resolve meta schema search path*/
    r = ResolvePath(&envResolvedPath, NULL, GetCoreSchemaPath(), SEARCH_PATTERN_DIRECTORY, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    //Update the cache with meta schema
    r = GetSchemaFromSingleMOF(miApp, deserializer, options, envResolvedPath, METACONFIGSCHEMA_FILENAME, miClassArray, NULL, extendedError);
    DSC_free(envResolvedPath);
    if( r != MI_RESULT_OK)
    {
        return r;
    }
    pathsForSchemas = (MI_Char**)DSC_malloc(NUM_PATHS_TO_LOOK_FOR_PROVIDERS * sizeof(MI_Char*), NitsHere());
    if( pathsForSchemas == NULL)
    {
        return MI_RESULT_FAILED;
    }
    pathsForSchemas[0] = (MI_Char*)GetSchemaSearchPath();
    pathsForSchemas[1] = (MI_Char*)GetSchemaSearchPathProgFiles();
    for (count = 0; count < NUM_PATHS_TO_LOOK_FOR_PROVIDERS; count++)
    {
        r= UpdateClassCacheWithSchemas(miApp,deserializer,options,miClassArray,extendedError,pathsForSchemas[count]);
        if( r != MI_RESULT_OK)
        {
            DSC_free(pathsForSchemas);
            return r;
        }
    }
    DSC_free(pathsForSchemas);
    return MI_RESULT_OK;
}

MI_Result UpdateClassCacheWithSchemas(_In_ MI_Application *miApp,
                            _In_ MI_Deserializer *deserializer,
                            _In_ MI_OperationOptions * options,
                            _Inout_ MI_ClassA *miClassArray,
                            _Outptr_result_maybenull_ MI_Instance **extendedError,
                            _In_z_ const MI_Char * schemaPath)
{
    MI_Char *envResolvedPath = NULL;
    Internal_Dir *dirHandle = NULL;
    MI_Result r = MI_RESULT_OK;
    Internal_DirEnt *dirEntry = NULL;

    /* Resolve schema search path*/
    r = ResolvePath(&envResolvedPath, NULL, schemaPath, NULL, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    /*Do actual search using search path*/

    dirHandle = Internal_Dir_Open(envResolvedPath, NitsHere() );
    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(envResolvedPath);
        if( dirHandle != NULL )
            Internal_Dir_Close( dirHandle);

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
    }
    dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    while( dirEntry != NULL )
    {
        /* Only process directories as modules are expected to have a directory per module.*/
        if( (dirEntry->isDir) &&
            (Tcscasecmp(MI_T(".."), dirEntry->name)!=0) &&
            (Tcscasecmp(MI_T("."), dirEntry->name)!=0))
        {
            r = UpdateClassCache(miApp, deserializer, options, envResolvedPath, dirEntry->name, miClassArray, extendedError);
            if( r != MI_RESULT_OK)
            {
                DSC_free(envResolvedPath);
                Internal_Dir_Close( dirHandle);
                return r;
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    }

    /*Cleanup*/
    Internal_Dir_Close( dirHandle);
    DSC_free(envResolvedPath);
    return MI_RESULT_OK;
}


/* Caller will clean up miClassArray*/

MI_Result UpdateClassCache(_In_ MI_Application *miApp,
                           _In_ MI_Deserializer *deserializer,
                           _In_ MI_OperationOptions * options,
                           _In_z_ MI_Char *rootPath,
                           _In_z_ MI_Char *directoryPath,
                           _Inout_ MI_ClassA *miClassArray,
                           _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    int result = 0;
    Internal_Dir *dirHandle = NULL;
    Internal_DirEnt *dirEntry = NULL;

    /*Form full path to schema module*/
    MI_Char *fullPath = NULL;
    MI_Uint32 fullPathLength = (MI_Uint32) (Tcslen(rootPath) + 1 + Tcslen(directoryPath) + 1) ; // rootpath\directorypath

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    fullPath = (MI_Char*)DSC_malloc(fullPathLength* sizeof(MI_Char), NitsHere());
    if( fullPath == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }
#if defined(_MSC_VER)
    result = Stprintf(fullPath, fullPathLength, MI_T("%T\\%T"), rootPath, directoryPath);
#else
    result = Stprintf(fullPath, fullPathLength, MI_T("%T/%T"), rootPath, directoryPath);
#endif

    if( result <= 0 || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        return GetCimMIError(result, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }
    /*Find schema files*/
    dirHandle = Internal_Dir_Open(fullPath, NitsHere() );

    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        if( dirHandle != NULL )
            Internal_Dir_Close( dirHandle);

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
    }
    dirEntry =  Internal_Dir_Read(dirHandle, SEARCH_PATTERN_SCHEMA);
    while(dirEntry != NULL)
    {
        /* Only process files*/
        if( !dirEntry->isDir)
        {
            r = GetSchemaFromSingleMOF(miApp, deserializer, options, fullPath, dirEntry->name, miClassArray, NULL, extendedError);
            if( r != MI_RESULT_OK)
            {
                DSC_free(fullPath);
                Internal_Dir_Close( dirHandle);
                return r;
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, SEARCH_PATTERN_SCHEMA);
    }

    /*Update Cache*/
    DSC_free(fullPath);
    Internal_Dir_Close( dirHandle);

    return MI_RESULT_OK;
}


MI_Result UpdateRegistrationInstanceCache(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _In_z_ MI_Char *rootPath,
                                          _In_z_ MI_Char *directoryPath,
                                          _Inout_ MI_InstanceA *miInstanceArray,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    int result = 0;
    Internal_Dir *dirHandle = NULL;
    Internal_DirEnt *dirEntry = NULL;
    MI_InstanceA miTempInstanceArray = {0};

    /*Form full path to schema module*/
    MI_Char *fullPath = NULL;
    MI_Uint32 fullPathLength = (MI_Uint32)(Tcslen(rootPath) + 1 + Tcslen(directoryPath) + 1) ; // rootpath\directorypath
    MI_Uint32 fullFilePathLength = 0;
    MI_Char *fullFilePath = NULL;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    fullPath = (MI_Char*)DSC_malloc(fullPathLength* sizeof(MI_Char), NitsHere());
    if( fullPath == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }
#if defined(_MSC_VER)
    result = Stprintf(fullPath, fullPathLength, MI_T("%T\\%T"), rootPath, directoryPath);
#else
    result = Stprintf(fullPath, fullPathLength, MI_T("%T/%T"), rootPath, directoryPath);
#endif

    if( result <=0 || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }

    /*Find schema files*/
    dirHandle = Internal_Dir_Open(fullPath, NitsHere() );

    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        if( dirHandle != NULL )
            Internal_Dir_Close( dirHandle);

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
    }
    dirEntry =  Internal_Dir_Read(dirHandle, SEARCH_PATTERN_REGISTRATIONINSTANCE);
    while( dirEntry != NULL)
    {
        /* Only process files*/
        if( !dirEntry->isDir)
        {
            fullFilePathLength = (MI_Uint32)(Tcslen(fullPath) + 1 + Tcslen(dirEntry->name) + 1) ; // mofModulePath\schemaFileName
            fullFilePath = (MI_Char*)DSC_malloc(fullFilePathLength* sizeof(MI_Char), NitsHere());
            if( fullFilePath == NULL)
            {
                CleanUpInstanceCache(&miTempInstanceArray);
                DSC_free(fullPath);
                Internal_Dir_Close( dirHandle);
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
            }
#if defined(_MSC_VER)
            result = Stprintf(fullFilePath, fullFilePathLength, MI_T("%T\\%T"), fullPath, dirEntry->name);
#else
            result = Stprintf(fullFilePath, fullFilePathLength, MI_T("%T/%T"), fullPath, dirEntry->name);
#endif

            if( result <=0 || NitsShouldFault(NitsHere(), NitsAutomatic))
            {
                DSC_free(fullFilePath);
                CleanUpInstanceCache(&miTempInstanceArray);
                DSC_free(fullPath);
                Internal_Dir_Close( dirHandle);
                return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_PRINTF_ERROR);
            }
            r = GetInstanceFromSingleMOF(moduleManager, VALIDATE_REGISTRATION_INSTANCE, miApp, deserializer, options, strictOptions, classArray, fullFilePath, &miTempInstanceArray, extendedError);
            DSC_free(fullFilePath);
            if( r != MI_RESULT_OK)
            {
                CleanUpInstanceCache(&miTempInstanceArray);
                DSC_free(fullPath);
                Internal_Dir_Close( dirHandle);
                return r;
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, SEARCH_PATTERN_REGISTRATIONINSTANCE);
    }

    /*Update Cache*/
    DSC_free(fullPath);
    Internal_Dir_Close( dirHandle);

    if( r == MI_RESULT_OK)
    {
        r = UpdateInstanceArray(&miTempInstanceArray, miInstanceArray, extendedError, MI_FALSE);
    }
    if( r != MI_RESULT_OK)
    {
        CleanUpInstanceCache(&miTempInstanceArray);
        return r;
    }

    return MI_RESULT_OK;
}



const ModuleManagerFT g_ModuleManagerFT = {
    ModuleManager_Close,
    ModuleManager_LoadInstanceDocument,
    ModuleManager_LoadInstanceDocumentFromLocation,
    ModuleManager_GetRegistrationInstance,
    ModuleManager_GetProviderCompatibleInstance,
    ModuleManager_Update
};



/*Function to get all the instances in a single array from a file*/
MI_Result GetArrayInstancesFromSingleMof(_In_ ModuleManager *moduleManager,
    MI_Uint32 flags,
    _In_z_  const MI_Char *documentLocation,
    MI_InstanceA * miInstanceArray,
    MI_Instance **extendedError,
    MI_Boolean shouldUseStrictOptions)
{
    MI_Result r = MI_RESULT_OK;
    MI_ClassA miClassArray = { 0 };
    ModuleLoaderObject *moduleLoader = NULL;
    DSC_EventWriteMessageLoadingInstance(documentLocation);

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if (r != MI_RESULT_OK)
    {
        return r;
    }


    moduleLoader = (ModuleLoaderObject*)moduleManager->reserved2;
    miClassArray.size = moduleLoader->schemaCount;
    miClassArray.data = moduleLoader->providerSchema;
    if (shouldUseStrictOptions == MI_TRUE)
    {
        r = GetInstanceFromSingleMOF(moduleManager, flags | VALIDATE_DOCUMENT_INSTANCE,
            moduleLoader->application, moduleLoader->deserializer,
            moduleLoader->options, moduleLoader->strictOptions, &miClassArray,
            documentLocation, miInstanceArray, extendedError);
    }
    else
    {
        r = GetInstanceFromSingleMOF(NULL, flags | VALIDATE_DOCUMENT_INSTANCE,
            moduleLoader->application, moduleLoader->deserializer,
            moduleLoader->options, moduleLoader->options, &miClassArray,
            documentLocation, miInstanceArray, extendedError);
    }
    return r;
}
