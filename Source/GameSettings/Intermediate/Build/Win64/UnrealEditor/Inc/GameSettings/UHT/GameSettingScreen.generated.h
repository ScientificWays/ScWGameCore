// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/GameSettingScreen.h"

#ifdef GAMESETTINGS_GameSettingScreen_generated_h
#error "GameSettingScreen.generated.h already included, missing '#pragma once' in GameSettingScreen.h"
#endif
#define GAMESETTINGS_GameSettingScreen_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UGameSettingCollection;

// ********** Begin Class UGameSettingScreen *******************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHaveSettingsBeenChanged); \
	DECLARE_FUNCTION(execApplyChanges); \
	DECLARE_FUNCTION(execCancelChanges); \
	DECLARE_FUNCTION(execGetSettingCollection); \
	DECLARE_FUNCTION(execAttemptToPopNavigation); \
	DECLARE_FUNCTION(execOnSettingsDirtyStateChanged); \
	DECLARE_FUNCTION(execNavigateToSettings); \
	DECLARE_FUNCTION(execNavigateToSetting);


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_CALLBACK_WRAPPERS
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingScreen_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingScreen(); \
	friend struct Z_Construct_UClass_UGameSettingScreen_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingScreen_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingScreen, UCommonActivatableWidget, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingScreen_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingScreen)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESETTINGS_API UGameSettingScreen(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingScreen(UGameSettingScreen&&) = delete; \
	UGameSettingScreen(const UGameSettingScreen&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingScreen); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingScreen); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameSettingScreen) \
	GAMESETTINGS_API virtual ~UGameSettingScreen();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_25_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_CALLBACK_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingScreen;

// ********** End Class UGameSettingScreen *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingScreen_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
