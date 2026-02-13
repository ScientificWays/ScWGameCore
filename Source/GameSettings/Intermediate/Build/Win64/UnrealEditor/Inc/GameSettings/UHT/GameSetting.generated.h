// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameSetting.h"

#ifdef GAMESETTINGS_GameSetting_generated_h
#error "GameSetting.generated.h already included, missing '#pragma once' in GameSetting.h"
#endif
#define GAMESETTINGS_GameSetting_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

enum class ESlateVisibility : uint8;
struct FGameplayTagContainer;

// ********** Begin Class UGameSetting *************************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetWarningRichText); \
	DECLARE_FUNCTION(execGetDynamicDetails); \
	DECLARE_FUNCTION(execGetTags); \
	DECLARE_FUNCTION(execGetDescriptionRichText); \
	DECLARE_FUNCTION(execGetDisplayNameVisibility); \
	DECLARE_FUNCTION(execGetDisplayName); \
	DECLARE_FUNCTION(execGetDevName);


GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSetting_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSetting(); \
	friend struct Z_Construct_UClass_UGameSetting_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSetting_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSetting, UObject, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSetting_NoRegister) \
	DECLARE_SERIALIZER(UGameSetting)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h_29_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSetting(UGameSetting&&) = delete; \
	UGameSetting(const UGameSetting&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSetting); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSetting); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(UGameSetting) \
	GAMESETTINGS_API virtual ~UGameSetting();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h_26_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h_29_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSetting;

// ********** End Class UGameSetting ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSetting_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
