// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "LoadingScreenManager.h"

#ifdef COMMONLOADINGSCREEN_LoadingScreenManager_generated_h
#error "LoadingScreenManager.generated.h already included, missing '#pragma once' in LoadingScreenManager.h"
#endif
#define COMMONLOADINGSCREEN_LoadingScreenManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ULoadingScreenManager ****************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetDebugReasonForShowingOrHidingLoadingScreen);


COMMONLOADINGSCREEN_API UClass* Z_Construct_UClass_ULoadingScreenManager_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h_30_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULoadingScreenManager(); \
	friend struct Z_Construct_UClass_ULoadingScreenManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend COMMONLOADINGSCREEN_API UClass* Z_Construct_UClass_ULoadingScreenManager_NoRegister(); \
public: \
	DECLARE_CLASS2(ULoadingScreenManager, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonLoadingScreen"), Z_Construct_UClass_ULoadingScreenManager_NoRegister) \
	DECLARE_SERIALIZER(ULoadingScreenManager)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h_30_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	COMMONLOADINGSCREEN_API ULoadingScreenManager(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ULoadingScreenManager(ULoadingScreenManager&&) = delete; \
	ULoadingScreenManager(const ULoadingScreenManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(COMMONLOADINGSCREEN_API, ULoadingScreenManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULoadingScreenManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULoadingScreenManager) \
	COMMONLOADINGSCREEN_API virtual ~ULoadingScreenManager();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h_27_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h_30_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h_30_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h_30_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ULoadingScreenManager;

// ********** End Class ULoadingScreenManager ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingScreenManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
