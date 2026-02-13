// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/GameSettingPanel.h"

#ifdef GAMESETTINGS_GameSettingPanel_generated_h
#error "GameSettingPanel.generated.h already included, missing '#pragma once' in GameSettingPanel.h"
#endif
#define GAMESETTINGS_GameSettingPanel_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UGameSetting;
struct FGameplayTag;

// ********** Begin Delegate FOnExecuteNamedActionBP ***********************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingPanel_h_109_DELEGATE \
static GAMESETTINGS_API void FOnExecuteNamedActionBP_DelegateWrapper(const FMulticastScriptDelegate& OnExecuteNamedActionBP, UGameSetting* Setting, FGameplayTag Action);


// ********** End Delegate FOnExecuteNamedActionBP *************************************************

// ********** Begin Class UGameSettingPanel ********************************************************
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingPanel_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingPanel_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingPanel(); \
	friend struct Z_Construct_UClass_UGameSettingPanel_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingPanel_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingPanel, UCommonUserWidget, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingPanel_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingPanel)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingPanel_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingPanel(UGameSettingPanel&&) = delete; \
	UGameSettingPanel(const UGameSettingPanel&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingPanel); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingPanel); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(UGameSettingPanel) \
	GAMESETTINGS_API virtual ~UGameSettingPanel();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingPanel_h_25_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingPanel_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingPanel_h_28_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingPanel_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingPanel;

// ********** End Class UGameSettingPanel **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingPanel_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
