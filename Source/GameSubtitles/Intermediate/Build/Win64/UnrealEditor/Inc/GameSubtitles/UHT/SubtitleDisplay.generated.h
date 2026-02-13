// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/SubtitleDisplay.h"

#ifdef GAMESUBTITLES_SubtitleDisplay_generated_h
#error "SubtitleDisplay.generated.h already included, missing '#pragma once' in SubtitleDisplay.h"
#endif
#define GAMESUBTITLES_SubtitleDisplay_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class USubtitleDisplay *********************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h_20_RPC_WRAPPERS \
	DECLARE_FUNCTION(execHasSubtitles);


GAMESUBTITLES_API UClass* Z_Construct_UClass_USubtitleDisplay_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h_20_INCLASS \
private: \
	static void StaticRegisterNativesUSubtitleDisplay(); \
	friend struct Z_Construct_UClass_USubtitleDisplay_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESUBTITLES_API UClass* Z_Construct_UClass_USubtitleDisplay_NoRegister(); \
public: \
	DECLARE_CLASS2(USubtitleDisplay, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GameSubtitles"), Z_Construct_UClass_USubtitleDisplay_NoRegister) \
	DECLARE_SERIALIZER(USubtitleDisplay)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESUBTITLES_API USubtitleDisplay(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USubtitleDisplay) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESUBTITLES_API, USubtitleDisplay); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USubtitleDisplay); \
	/** Deleted move- and copy-constructors, should never be used */ \
	USubtitleDisplay(USubtitleDisplay&&) = delete; \
	USubtitleDisplay(const USubtitleDisplay&) = delete; \
	GAMESUBTITLES_API virtual ~USubtitleDisplay();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h_17_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h_20_RPC_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h_20_INCLASS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class USubtitleDisplay;

// ********** End Class USubtitleDisplay ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Widgets_SubtitleDisplay_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
