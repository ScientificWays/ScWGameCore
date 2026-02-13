// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Players/MediaSubtitlesPlayer.h"

#ifdef GAMESUBTITLES_MediaSubtitlesPlayer_generated_h
#error "MediaSubtitlesPlayer.generated.h already included, missing '#pragma once' in MediaSubtitlesPlayer.h"
#endif
#define GAMESUBTITLES_MediaSubtitlesPlayer_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UMediaPlayer;
class UOverlays;

// ********** Begin Class UMediaSubtitlesPlayer ****************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h_27_RPC_WRAPPERS \
	DECLARE_FUNCTION(execBindToMediaPlayer); \
	DECLARE_FUNCTION(execSetSubtitles); \
	DECLARE_FUNCTION(execStop); \
	DECLARE_FUNCTION(execPlay);


GAMESUBTITLES_API UClass* Z_Construct_UClass_UMediaSubtitlesPlayer_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h_27_INCLASS \
private: \
	static void StaticRegisterNativesUMediaSubtitlesPlayer(); \
	friend struct Z_Construct_UClass_UMediaSubtitlesPlayer_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESUBTITLES_API UClass* Z_Construct_UClass_UMediaSubtitlesPlayer_NoRegister(); \
public: \
	DECLARE_CLASS2(UMediaSubtitlesPlayer, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GameSubtitles"), Z_Construct_UClass_UMediaSubtitlesPlayer_NoRegister) \
	DECLARE_SERIALIZER(UMediaSubtitlesPlayer)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h_27_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESUBTITLES_API UMediaSubtitlesPlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMediaSubtitlesPlayer) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESUBTITLES_API, UMediaSubtitlesPlayer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMediaSubtitlesPlayer); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UMediaSubtitlesPlayer(UMediaSubtitlesPlayer&&) = delete; \
	UMediaSubtitlesPlayer(const UMediaSubtitlesPlayer&) = delete; \
	GAMESUBTITLES_API virtual ~UMediaSubtitlesPlayer();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h_22_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h_27_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h_27_RPC_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h_27_INCLASS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h_27_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UMediaSubtitlesPlayer;

// ********** End Class UMediaSubtitlesPlayer ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSubtitles_Source_Public_Players_MediaSubtitlesPlayer_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
