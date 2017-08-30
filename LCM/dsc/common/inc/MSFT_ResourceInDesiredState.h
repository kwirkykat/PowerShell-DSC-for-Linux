/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_ResourceInDesiredState_h
#define _MSFT_ResourceInDesiredState_h

#include <MI.h>
#include "MSFT_DSCResource.h"

/*
**==============================================================================
**
** MSFT_ResourceInDesiredState [MSFT_ResourceInDesiredState]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_ResourceInDesiredState /* extends MSFT_DSCResource */
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
    /* MSFT_ResourceInDesiredState properties */
}
MSFT_ResourceInDesiredState;

typedef struct _MSFT_ResourceInDesiredState_Ref
{
    MSFT_ResourceInDesiredState* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ResourceInDesiredState_Ref;

typedef struct _MSFT_ResourceInDesiredState_ConstRef
{
    MI_CONST MSFT_ResourceInDesiredState* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ResourceInDesiredState_ConstRef;

typedef struct _MSFT_ResourceInDesiredState_Array
{
    struct _MSFT_ResourceInDesiredState** data;
    MI_Uint32 size;
}
MSFT_ResourceInDesiredState_Array;

typedef struct _MSFT_ResourceInDesiredState_ConstArray
{
    struct _MSFT_ResourceInDesiredState MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_ResourceInDesiredState_ConstArray;

typedef struct _MSFT_ResourceInDesiredState_ArrayRef
{
    MSFT_ResourceInDesiredState_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ResourceInDesiredState_ArrayRef;

typedef struct _MSFT_ResourceInDesiredState_ConstArrayRef
{
    MSFT_ResourceInDesiredState_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ResourceInDesiredState_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_ResourceInDesiredState_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Construct(
    _Out_ MSFT_ResourceInDesiredState* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_ResourceInDesiredState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clone(
    _In_ const MSFT_ResourceInDesiredState* self,
    _Outptr_ MSFT_ResourceInDesiredState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_ResourceInDesiredState_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_ResourceInDesiredState_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Destruct(_Inout_ MSFT_ResourceInDesiredState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Delete(_Inout_ MSFT_ResourceInDesiredState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Post(
    _In_ const MSFT_ResourceInDesiredState* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_ResourceId(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_ResourceId(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_ResourceId(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_SourceInfo(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_SourceInfo(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_SourceInfo(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_DependsOn(
    _Inout_ MSFT_ResourceInDesiredState* self,
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

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_DependsOn(
    _Inout_ MSFT_ResourceInDesiredState* self,
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

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_DependsOn(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_ModuleName(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_ModuleName(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_ModuleName(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_ModuleVersion(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_ModuleVersion(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_ModuleVersion(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_ConfigurationName(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_ConfigurationName(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_ConfigurationName(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_PsDscRunAsCredential(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_PsDscRunAsCredential(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_PsDscRunAsCredential(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_ResourceName(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_ResourceName(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_ResourceName(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_InstanceName(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_InstanceName(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_InstanceName(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_InDesiredState(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->InDesiredState)->value = x;
    ((MI_BooleanField*)&self->InDesiredState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_InDesiredState(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    memset((void*)&self->InDesiredState, 0, sizeof(self->InDesiredState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_StateChanged(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->StateChanged)->value = x;
    ((MI_BooleanField*)&self->StateChanged)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_StateChanged(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    memset((void*)&self->StateChanged, 0, sizeof(self->StateChanged));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_StartDate(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->StartDate)->value = x;
    ((MI_DatetimeField*)&self->StartDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_StartDate(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    memset((void*)&self->StartDate, 0, sizeof(self->StartDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_DurationInSeconds(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_ MI_Real64 x)
{
    ((MI_Real64Field*)&self->DurationInSeconds)->value = x;
    ((MI_Real64Field*)&self->DurationInSeconds)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_DurationInSeconds(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    memset((void*)&self->DurationInSeconds, 0, sizeof(self->DurationInSeconds));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_RebootRequested(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->RebootRequested)->value = x;
    ((MI_BooleanField*)&self->RebootRequested)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_RebootRequested(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    memset((void*)&self->RebootRequested, 0, sizeof(self->RebootRequested));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_InitialState(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_InitialState(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_InitialState(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_FinalState(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_FinalState(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_FinalState(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Set_Error(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_SetPtr_Error(
    _Inout_ MSFT_ResourceInDesiredState* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ResourceInDesiredState_Clear_Error(
    _Inout_ MSFT_ResourceInDesiredState* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}


#endif /* _MSFT_ResourceInDesiredState_h */
