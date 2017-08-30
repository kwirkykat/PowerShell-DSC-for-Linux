/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_DSCConfigurationStatus_h
#define _MSFT_DSCConfigurationStatus_h

#include <MI.h>
#include "MSFT_DSCMetaConfiguration.h"
#include "MSFT_ResourceInDesiredState.h"
#include "MSFT_ResourceNotInDesiredState.h"
#include "MSFT_ResourceChanged.h"

/*
**==============================================================================
**
** MSFT_DSCConfigurationStatus [MSFT_DSCConfigurationStatus]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_DSCConfigurationStatus
{
    MI_Instance __instance;
    /* MSFT_DSCConfigurationStatus properties */
    MI_ConstStringField Status;
    MI_ConstStringField Error;
    MI_ConstDatetimeField StartDate;
    MI_ConstUint32Field DurationInSeconds;
    MI_ConstBooleanField RebootRequested;
    MI_ConstStringField Type;
    MI_ConstStringField JobID;
    MI_ConstStringField MetaData;
    MI_ConstUint32Field NumberOfResources;
    MI_ConstStringField Mode;
    MI_ConstStringField LCMVersion;
    MI_ConstStringField HostName;
    MI_ConstStringAField IPV4Addresses;
    MI_ConstStringAField IPV6Addresses;
    MI_ConstStringAField MACAddresses;
    MSFT_DSCMetaConfiguration_ConstRef MetaConfiguration;
    MSFT_ResourceInDesiredState_ConstArrayRef ResourcesInDesiredState;
    MSFT_ResourceNotInDesiredState_ConstArrayRef ResourcesNotInDesiredState;
    MSFT_ResourceChanged_ConstArrayRef ResourcesChanged;
    MI_ConstStringField Locale;
}
MSFT_DSCConfigurationStatus;

typedef struct _MSFT_DSCConfigurationStatus_Ref
{
    MSFT_DSCConfigurationStatus* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCConfigurationStatus_Ref;

typedef struct _MSFT_DSCConfigurationStatus_ConstRef
{
    MI_CONST MSFT_DSCConfigurationStatus* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCConfigurationStatus_ConstRef;

typedef struct _MSFT_DSCConfigurationStatus_Array
{
    struct _MSFT_DSCConfigurationStatus** data;
    MI_Uint32 size;
}
MSFT_DSCConfigurationStatus_Array;

typedef struct _MSFT_DSCConfigurationStatus_ConstArray
{
    struct _MSFT_DSCConfigurationStatus MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_DSCConfigurationStatus_ConstArray;

typedef struct _MSFT_DSCConfigurationStatus_ArrayRef
{
    MSFT_DSCConfigurationStatus_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCConfigurationStatus_ArrayRef;

typedef struct _MSFT_DSCConfigurationStatus_ConstArrayRef
{
    MSFT_DSCConfigurationStatus_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCConfigurationStatus_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_DSCConfigurationStatus_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Construct(
    _Out_ MSFT_DSCConfigurationStatus* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_DSCConfigurationStatus_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clone(
    _In_ const MSFT_DSCConfigurationStatus* self,
    _Outptr_ MSFT_DSCConfigurationStatus** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_DSCConfigurationStatus_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_DSCConfigurationStatus_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Destruct(_Inout_ MSFT_DSCConfigurationStatus* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Delete(_Inout_ MSFT_DSCConfigurationStatus* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Post(
    _In_ const MSFT_DSCConfigurationStatus* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_Status(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_Status(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_Status(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_Error(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_Error(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_Error(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_StartDate(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->StartDate)->value = x;
    ((MI_DatetimeField*)&self->StartDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_StartDate(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    memset((void*)&self->StartDate, 0, sizeof(self->StartDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_DurationInSeconds(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->DurationInSeconds)->value = x;
    ((MI_Uint32Field*)&self->DurationInSeconds)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_DurationInSeconds(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    memset((void*)&self->DurationInSeconds, 0, sizeof(self->DurationInSeconds));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_RebootRequested(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->RebootRequested)->value = x;
    ((MI_BooleanField*)&self->RebootRequested)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_RebootRequested(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    memset((void*)&self->RebootRequested, 0, sizeof(self->RebootRequested));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_Type(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_Type(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_Type(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_JobID(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_JobID(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_JobID(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_MetaData(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_MetaData(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_MetaData(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_NumberOfResources(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->NumberOfResources)->value = x;
    ((MI_Uint32Field*)&self->NumberOfResources)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_NumberOfResources(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    memset((void*)&self->NumberOfResources, 0, sizeof(self->NumberOfResources));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_Mode(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_Mode(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_Mode(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_LCMVersion(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_LCMVersion(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_LCMVersion(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_HostName(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_HostName(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_HostName(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_IPV4Addresses(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_IPV4Addresses(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_IPV4Addresses(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_IPV6Addresses(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_IPV6Addresses(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_IPV6Addresses(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_MACAddresses(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_MACAddresses(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_MACAddresses(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_MetaConfiguration(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_ const MSFT_DSCMetaConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_MetaConfiguration(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_ const MSFT_DSCMetaConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_MetaConfiguration(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_ResourcesInDesiredState(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MSFT_ResourceInDesiredState * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_ResourcesInDesiredState(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MSFT_ResourceInDesiredState * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_ResourcesInDesiredState(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_ResourcesNotInDesiredState(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MSFT_ResourceNotInDesiredState * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_ResourcesNotInDesiredState(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MSFT_ResourceNotInDesiredState * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_ResourcesNotInDesiredState(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_ResourcesChanged(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MSFT_ResourceChanged * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_ResourcesChanged(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_reads_opt_(size) const MSFT_ResourceChanged * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_ResourcesChanged(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Set_Locale(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_SetPtr_Locale(
    _Inout_ MSFT_DSCConfigurationStatus* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCConfigurationStatus_Clear_Locale(
    _Inout_ MSFT_DSCConfigurationStatus* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}


#endif /* _MSFT_DSCConfigurationStatus_h */
