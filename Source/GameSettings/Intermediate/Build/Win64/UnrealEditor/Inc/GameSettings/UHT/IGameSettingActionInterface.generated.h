// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/IGameSettingActionInterface.h"

#ifdef GAMESETTINGS_IGameSettingActionInterface_generated_h
#error "IGameSettingActionInterface.generated.h already included, missing '#pragma once' in IGameSettingActionInterface.h"
#endif
#define GAMESETTINGS_IGameSettingActionInterface_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UGameSetting;
struct FGameplayTag;

// ********** Begin Interface UGameSettingActionInterface ******************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual bool ExecuteActionForSetting_Implementation(FGameplayTag ActionTag, UGameSetting* InSetting) { return false; }; \
	DECLARE_FUNCTION(execExecuteActionForSetting);


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_CALLBACK_WRAPPERS
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingActionInterface_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESETTINGS_API UGameSettingActionInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameSettingActionInterface) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingActionInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingActionInterface); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingActionInterface(UGameSettingActionInterface&&) = delete; \
	UGameSettingActionInterface(const UGameSettingActionInterface&) = delete; \
	virtual ~UGameSettingActionInterface() = default;


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUGameSettingActionInterface(); \
	friend struct Z_Construct_UClass_UGameSettingActionInterface_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingActionInterface_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingActionInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingActionInterface_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingActionInterface)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_GENERATED_BODY_LEGACY \
		PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_GENERATED_UINTERFACE_BODY() \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_STANDARD_CONSTRUCTORS \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IGameSettingActionInterface() {} \
public: \
	typedef UGameSettingActionInterface UClassType; \
	typedef IGameSettingActionInterface ThisClass; \
	GAMESETTINGS_API static bool Execute_ExecuteActionForSetting(UObject* O, FGameplayTag ActionTag, UGameSetting* InSetting); \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_16_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_CALLBACK_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h_19_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingActionInterface;

// ********** End Interface UGameSettingActionInterface ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_IGameSettingActionInterface_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
