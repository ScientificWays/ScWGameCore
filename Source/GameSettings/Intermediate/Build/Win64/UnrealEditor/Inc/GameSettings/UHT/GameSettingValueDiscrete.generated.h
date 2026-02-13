// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameSettingValueDiscrete.h"

#ifdef GAMESETTINGS_GameSettingValueDiscrete_generated_h
#error "GameSettingValueDiscrete.generated.h already included, missing '#pragma once' in GameSettingValueDiscrete.h"
#endif
#define GAMESETTINGS_GameSettingValueDiscrete_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UGameSettingValueDiscrete ************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetDiscreteOptions); \
	DECLARE_FUNCTION(execGetDiscreteOptionDefaultIndex); \
	DECLARE_FUNCTION(execGetDiscreteOptionIndex);


GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscrete_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingValueDiscrete(); \
	friend struct Z_Construct_UClass_UGameSettingValueDiscrete_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscrete_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingValueDiscrete, UGameSettingValue, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingValueDiscrete_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingValueDiscrete)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h_17_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingValueDiscrete(UGameSettingValueDiscrete&&) = delete; \
	UGameSettingValueDiscrete(const UGameSettingValueDiscrete&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingValueDiscrete); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingValueDiscrete); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(UGameSettingValueDiscrete) \
	GAMESETTINGS_API virtual ~UGameSettingValueDiscrete();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h_14_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h_17_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingValueDiscrete;

// ********** End Class UGameSettingValueDiscrete **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscrete_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
