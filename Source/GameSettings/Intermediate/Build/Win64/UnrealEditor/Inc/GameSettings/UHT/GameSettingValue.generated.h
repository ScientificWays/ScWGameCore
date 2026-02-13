// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameSettingValue.h"

#ifdef GAMESETTINGS_GameSettingValue_generated_h
#error "GameSettingValue.generated.h already included, missing '#pragma once' in GameSettingValue.h"
#endif
#define GAMESETTINGS_GameSettingValue_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UGameSettingValue ********************************************************
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValue_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValue_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingValue(); \
	friend struct Z_Construct_UClass_UGameSettingValue_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValue_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingValue, UGameSetting, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingValue_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingValue)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValue_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingValue(UGameSettingValue&&) = delete; \
	UGameSettingValue(const UGameSettingValue&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingValue); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingValue); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(UGameSettingValue) \
	GAMESETTINGS_API virtual ~UGameSettingValue();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValue_h_21_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValue_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValue_h_24_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValue_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingValue;

// ********** End Class UGameSettingValue **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValue_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
