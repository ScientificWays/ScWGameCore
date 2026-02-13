// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SubtitleDisplayOptions.h"

#ifdef GAMESUBTITLES_SubtitleDisplayOptions_generated_h
#error "SubtitleDisplayOptions.generated.h already included, missing '#pragma once' in SubtitleDisplayOptions.h"
#endif
#define GAMESUBTITLES_SubtitleDisplayOptions_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class USubtitleDisplayOptions **************************************************
GAMESUBTITLES_API UClass* Z_Construct_UClass_USubtitleDisplayOptions_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_SubtitleDisplayOptions_h_58_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSubtitleDisplayOptions(); \
	friend struct Z_Construct_UClass_USubtitleDisplayOptions_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESUBTITLES_API UClass* Z_Construct_UClass_USubtitleDisplayOptions_NoRegister(); \
public: \
	DECLARE_CLASS2(USubtitleDisplayOptions, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GameSubtitles"), Z_Construct_UClass_USubtitleDisplayOptions_NoRegister) \
	DECLARE_SERIALIZER(USubtitleDisplayOptions)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_SubtitleDisplayOptions_h_58_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	USubtitleDisplayOptions(USubtitleDisplayOptions&&) = delete; \
	USubtitleDisplayOptions(const USubtitleDisplayOptions&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESUBTITLES_API, USubtitleDisplayOptions); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USubtitleDisplayOptions); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USubtitleDisplayOptions) \
	GAMESUBTITLES_API virtual ~USubtitleDisplayOptions();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_SubtitleDisplayOptions_h_55_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_SubtitleDisplayOptions_h_58_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_SubtitleDisplayOptions_h_58_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_SubtitleDisplayOptions_h_58_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class USubtitleDisplayOptions;

// ********** End Class USubtitleDisplayOptions ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_SubtitleDisplayOptions_h

// ********** Begin Enum ESubtitleDisplayTextSize **************************************************
#define FOREACH_ENUM_ESUBTITLEDISPLAYTEXTSIZE(op) \
	op(ESubtitleDisplayTextSize::ExtraSmall) \
	op(ESubtitleDisplayTextSize::Small) \
	op(ESubtitleDisplayTextSize::Medium) \
	op(ESubtitleDisplayTextSize::Large) \
	op(ESubtitleDisplayTextSize::ExtraLarge) 

enum class ESubtitleDisplayTextSize : uint8;
template<> struct TIsUEnumClass<ESubtitleDisplayTextSize> { enum { Value = true }; };
template<> GAMESUBTITLES_API UEnum* StaticEnum<ESubtitleDisplayTextSize>();
// ********** End Enum ESubtitleDisplayTextSize ****************************************************

// ********** Begin Enum ESubtitleDisplayTextColor *************************************************
#define FOREACH_ENUM_ESUBTITLEDISPLAYTEXTCOLOR(op) \
	op(ESubtitleDisplayTextColor::White) \
	op(ESubtitleDisplayTextColor::Yellow) 

enum class ESubtitleDisplayTextColor : uint8;
template<> struct TIsUEnumClass<ESubtitleDisplayTextColor> { enum { Value = true }; };
template<> GAMESUBTITLES_API UEnum* StaticEnum<ESubtitleDisplayTextColor>();
// ********** End Enum ESubtitleDisplayTextColor ***************************************************

// ********** Begin Enum ESubtitleDisplayTextBorder ************************************************
#define FOREACH_ENUM_ESUBTITLEDISPLAYTEXTBORDER(op) \
	op(ESubtitleDisplayTextBorder::None) \
	op(ESubtitleDisplayTextBorder::Outline) \
	op(ESubtitleDisplayTextBorder::DropShadow) 

enum class ESubtitleDisplayTextBorder : uint8;
template<> struct TIsUEnumClass<ESubtitleDisplayTextBorder> { enum { Value = true }; };
template<> GAMESUBTITLES_API UEnum* StaticEnum<ESubtitleDisplayTextBorder>();
// ********** End Enum ESubtitleDisplayTextBorder **************************************************

// ********** Begin Enum ESubtitleDisplayBackgroundOpacity *****************************************
#define FOREACH_ENUM_ESUBTITLEDISPLAYBACKGROUNDOPACITY(op) \
	op(ESubtitleDisplayBackgroundOpacity::Clear) \
	op(ESubtitleDisplayBackgroundOpacity::Low) \
	op(ESubtitleDisplayBackgroundOpacity::Medium) \
	op(ESubtitleDisplayBackgroundOpacity::High) \
	op(ESubtitleDisplayBackgroundOpacity::Solid) 

enum class ESubtitleDisplayBackgroundOpacity : uint8;
template<> struct TIsUEnumClass<ESubtitleDisplayBackgroundOpacity> { enum { Value = true }; };
template<> GAMESUBTITLES_API UEnum* StaticEnum<ESubtitleDisplayBackgroundOpacity>();
// ********** End Enum ESubtitleDisplayBackgroundOpacity *******************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
