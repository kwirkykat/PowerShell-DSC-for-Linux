/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_ResourceNotInDesiredState_h
#define _MSFT_ResourceNotInDesiredState_h

#include <MI.h>
#include "MSFT_DSCResource.h"

/*
**==============================================================================
**
** MSFT_ResourceNotInDesiredState [MSFT_ResourceNotInDesiredState]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_ResourceNotInDesiredState /* extends MSFT_DSCResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    MI_ConstStringField ResourceId;
    MI_ConstStringField SourceInfo;
    MI_ConstStringAField DependsOn;
    MI_ConstStringField ModuleName;
    MI_ConstStringField ModuleVersion;
    MI_ConstStringField ConfigurationName;
    MSFT_Credential_ConstRef PsDscRunAsCredential;
    /* MSFT_DSCResource properties */
    MI_ConstStringField ResourceName;
    MI_ConstStringField InstanceName;
    MI_ConstBooleanField InDesiredState;
    MI_ConstBooleanField StateChanged;
    MI_ConstDatetimeField StartDate;
    MI_ConstReal64Field DurationInSeconds;
    MI_ConstBooleanField RebootRequested;
    MI_ConstStringField InitialState;
    MI_ConstStringField FinalState;
    MI_ConstStringField Error;
    /* MSFT_ResourceNotInDesiredState properties */
}
MSFT_ResourceNotInDesiredState;

typedef struct _MSFT_ResourceNotInDesiredState_Ref
{
    MSFT_ResourceNotInDesiredState* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ResourceNotInDesiredState_Ref;

typedef struct _MSFT_ResourceNotInDesiredState_ConstRef
{
    MI_CONST MSFT_ResourceNotInDesiredState* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ResourceNotInDesiredState_ConstRef;

typedef struct _MSFT_ResourceNotInDesiredState_Array
{
    struct _MSFT_ResourceNotInDesiredState** data;
    MI_Uint32 size;
}
MSFT_ResourceNotInDesiredState_Array;

typedef struct _MSFT_ResourceNotInDesiredState_ConstArray
{
    struct _MSFT_ResourceNotInDesiredState MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_ResourceNotInDesiredState_ConstArray;

typedef struct _MSFT_ResourceNotInDesiredState_ArrayRef
{
    MSFT_ResourceNotInDesiredState_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ResourceNotInDesiredState_ArrayRef;

typedef struct _MSFT_ResourceNotInDesiredState_ConstArrayRef
{
    MSFT_ResourceNotInDesiredState_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ResourceNotInDesiredState_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_ResourceNotInDesiredState_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Construct(
    _Out_ MSFT_ResourceNotInDesiredState* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_ResourceNotInDesiredState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clone(
    _In_ const MSFT_ResourceNotInDesiredState* self,
    _Outptr_ MSFT_ResourceNotInDesiredState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_ResourceNotInDesiredState_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_ResourceNotInDesiredState_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Destruct(_Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Delete(_Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Post(
    _In_ const MSFT_ResourceNotInDesiredState* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_ResourceId(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_ResourceId(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_ResourceId(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_SourceInfo(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_SourceInfo(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_SourceInfo(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_DependsOn(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_DependsOn(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_DependsOn(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_ModuleName(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_ModuleName(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_ModuleName(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_ModuleVersion(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_ModuleVersion(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_ModuleVersion(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_ConfigurationName(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_ConfigurationName(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_ConfigurationName(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_PsDscRunAsCredential(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_PsDscRunAsCredential(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_PsDscRunAsCredential(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_ResourceName(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_ResourceName(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_ResourceName(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_InstanceName(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_InstanceName(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_InstanceName(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_InDesiredState(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->InDesiredState)->value = x;
    ((MI_BooleanField*)&self->InDesiredState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_InDesiredState(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    memset((void*)&self->InDesiredState, 0, sizeof(self->InDesiredState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_StateChanged(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->StateChanged)->value = x;
    ((MI_BooleanField*)&self->StateChanged)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_StateChanged(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    memset((void*)&self->StateChanged, 0, sizeof(self->StateChanged));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_StartDate(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->StartDate)->value = x;
    ((MI_DatetimeField*)&self->StartDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_StartDate(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    memset((void*)&self->StartDate, 0, sizeof(self->StartDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_DurationInSeconds(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_ MI_Real64 x)
{
    ((MI_Real64Field*)&self->DurationInSeconds)->value = x;
    ((MI_Real64Field*)&self->DurationInSeconds)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_DurationInSeconds(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    memset((void*)&self->DurationInSeconds, 0, sizeof(self->DurationInSeconds));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_RebootRequested(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->RebootRequested)->value = x;
    ((MI_BooleanField*)&self->RebootRequested)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_RebootRequested(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    memset((void*)&self->RebootRequested, 0, sizeof(self->RebootRequested));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_InitialState(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_InitialState(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_InitialState(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_FinalState(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_FinalState(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_FinalState(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Set_Error(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_SetPtr_Error(
    _Inout_ MSFT_ResourceNotInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceNotInDesiredState_Clear_Error(
    _Inout_ MSFT_ResourceNotInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}


#endif /* _MSFT_ResourceNotInDesiredState_h */
