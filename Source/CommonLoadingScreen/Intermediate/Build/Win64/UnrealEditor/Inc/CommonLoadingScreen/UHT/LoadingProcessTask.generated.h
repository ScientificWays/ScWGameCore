// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "LoadingProcessTask.h"

#ifdef COMMONLOADINGSCREEN_LoadingProcessTask_generated_h
#error "LoadingProcessTask.generated.h already included, missing '#pragma once' in LoadingProcessTask.h"
#endif
#define COMMONLOADINGSCREEN_LoadingProcessTask_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class ULoadingProcessTask;
class UObject;

// ********** Begin Class ULoadingProcessTask ******************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetShowLoadingScreenReason); \
	DECLARE_FUNCTION(execUnregister); \
	DECLARE_FUNCTION(execCreateLoadingScreenProcessTask);


COMMONLOADINGSCREEN_API UClass* Z_Construct_UClass_ULoadingProcessTask_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULoadingProcessTask(); \
	friend struct Z_Construct_UClass_ULoadingProcessTask_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend COMMONLOADINGSCREEN_API UClass* Z_Construct_UClass_ULoadingProcessTask_NoRegister(); \
public: \
	DECLARE_CLASS2(ULoadingProcessTask, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonLoadingScreen"), Z_Construct_UClass_ULoadingProcessTask_NoRegister) \
	DECLARE_SERIALIZER(ULoadingProcessTask) \
	virtual UObject* _getUObject() const override { return const_cast<ULoadingProcessTask*>(this); }


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h_17_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ULoadingProcessTask(ULoadingProcessTask&&) = delete; \
	ULoadingProcessTask(const ULoadingProcessTask&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(COMMONLOADINGSCREEN_API, ULoadingProcessTask); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULoadingProcessTask); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULoadingProcessTask) \
	COMMONLOADINGSCREEN_API virtual ~ULoadingProcessTask();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h_14_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h_17_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ULoadingProcessTask;

// ********** End Class ULoadingProcessTask ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessTask_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
