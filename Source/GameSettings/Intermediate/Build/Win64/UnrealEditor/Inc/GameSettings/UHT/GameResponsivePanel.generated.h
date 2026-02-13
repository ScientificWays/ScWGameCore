// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/Responsive/GameResponsivePanel.h"

#ifdef GAMESETTINGS_GameResponsivePanel_generated_h
#error "GameResponsivePanel.generated.h already included, missing '#pragma once' in GameResponsivePanel.h"
#endif
#define GAMESETTINGS_GameResponsivePanel_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UGameResponsivePanelSlot;
class UWidget;

// ********** Begin Class UGameResponsivePanel *****************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h_19_RPC_WRAPPERS \
	DECLARE_FUNCTION(execAddChildToGameResponsivePanel);


GAMESETTINGS_API UClass* Z_Construct_UClass_UGameResponsivePanel_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h_19_INCLASS \
private: \
	static void StaticRegisterNativesUGameResponsivePanel(); \
	friend struct Z_Construct_UClass_UGameResponsivePanel_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameResponsivePanel_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameResponsivePanel, UPanelWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameResponsivePanel_NoRegister) \
	DECLARE_SERIALIZER(UGameResponsivePanel)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameResponsivePanel(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameResponsivePanel) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameResponsivePanel); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameResponsivePanel); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameResponsivePanel(UGameResponsivePanel&&) = delete; \
	UGameResponsivePanel(const UGameResponsivePanel&) = delete; \
	NO_API virtual ~UGameResponsivePanel();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h_16_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h_19_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h_19_RPC_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h_19_INCLASS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h_19_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameResponsivePanel;

// ********** End Class UGameResponsivePanel *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanel_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
