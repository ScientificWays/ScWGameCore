// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/GameSettingListEntry.h"

#ifdef GAMESETTINGS_GameSettingListEntry_generated_h
#error "GameSettingListEntry.generated.h already included, missing '#pragma once' in GameSettingListEntry.h"
#endif
#define GAMESETTINGS_GameSettingListEntry_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UWidget;

// ********** Begin Class UGameSettingListEntryBase ************************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_39_CALLBACK_WRAPPERS
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntryBase_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_39_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingListEntryBase(); \
	friend struct Z_Construct_UClass_UGameSettingListEntryBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntryBase_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingListEntryBase, UCommonUserWidget, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingListEntryBase_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingListEntryBase) \
	virtual UObject* _getUObject() const override { return const_cast<UGameSettingListEntryBase*>(this); }


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_39_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESETTINGS_API UGameSettingListEntryBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingListEntryBase(UGameSettingListEntryBase&&) = delete; \
	UGameSettingListEntryBase(const UGameSettingListEntryBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingListEntryBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingListEntryBase); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameSettingListEntryBase) \
	GAMESETTINGS_API virtual ~UGameSettingListEntryBase();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_36_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_39_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_39_CALLBACK_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_39_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_39_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingListEntryBase;

// ********** End Class UGameSettingListEntryBase **************************************************

// ********** Begin Class UGameSettingListEntry_Setting ********************************************
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntry_Setting_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_81_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingListEntry_Setting(); \
	friend struct Z_Construct_UClass_UGameSettingListEntry_Setting_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntry_Setting_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingListEntry_Setting, UGameSettingListEntryBase, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingListEntry_Setting_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingListEntry_Setting)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_81_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESETTINGS_API UGameSettingListEntry_Setting(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingListEntry_Setting(UGameSettingListEntry_Setting&&) = delete; \
	UGameSettingListEntry_Setting(const UGameSettingListEntry_Setting&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingListEntry_Setting); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingListEntry_Setting); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameSettingListEntry_Setting) \
	GAMESETTINGS_API virtual ~UGameSettingListEntry_Setting();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_78_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_81_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_81_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_81_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingListEntry_Setting;

// ********** End Class UGameSettingListEntry_Setting **********************************************

// ********** Begin Class UGameSettingListEntrySetting_Discrete ************************************
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntrySetting_Discrete_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_99_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingListEntrySetting_Discrete(); \
	friend struct Z_Construct_UClass_UGameSettingListEntrySetting_Discrete_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntrySetting_Discrete_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingListEntrySetting_Discrete, UGameSettingListEntry_Setting, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingListEntrySetting_Discrete_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingListEntrySetting_Discrete)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_99_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESETTINGS_API UGameSettingListEntrySetting_Discrete(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingListEntrySetting_Discrete(UGameSettingListEntrySetting_Discrete&&) = delete; \
	UGameSettingListEntrySetting_Discrete(const UGameSettingListEntrySetting_Discrete&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingListEntrySetting_Discrete); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingListEntrySetting_Discrete); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameSettingListEntrySetting_Discrete) \
	GAMESETTINGS_API virtual ~UGameSettingListEntrySetting_Discrete();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_96_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_99_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_99_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_99_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingListEntrySetting_Discrete;

// ********** End Class UGameSettingListEntrySetting_Discrete **************************************

// ********** Begin Class UGameSettingListEntrySetting_Scalar **************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleSliderCaptureEnded); \
	DECLARE_FUNCTION(execHandleSliderValueChanged);


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_CALLBACK_WRAPPERS
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntrySetting_Scalar_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingListEntrySetting_Scalar(); \
	friend struct Z_Construct_UClass_UGameSettingListEntrySetting_Scalar_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntrySetting_Scalar_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingListEntrySetting_Scalar, UGameSettingListEntry_Setting, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingListEntrySetting_Scalar_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingListEntrySetting_Scalar)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESETTINGS_API UGameSettingListEntrySetting_Scalar(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingListEntrySetting_Scalar(UGameSettingListEntrySetting_Scalar&&) = delete; \
	UGameSettingListEntrySetting_Scalar(const UGameSettingListEntrySetting_Scalar&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingListEntrySetting_Scalar); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingListEntrySetting_Scalar); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameSettingListEntrySetting_Scalar) \
	GAMESETTINGS_API virtual ~UGameSettingListEntrySetting_Scalar();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_139_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_CALLBACK_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_142_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingListEntrySetting_Scalar;

// ********** End Class UGameSettingListEntrySetting_Scalar ****************************************

// ********** Begin Class UGameSettingListEntrySetting_Action **************************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_189_CALLBACK_WRAPPERS
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntrySetting_Action_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_189_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingListEntrySetting_Action(); \
	friend struct Z_Construct_UClass_UGameSettingListEntrySetting_Action_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntrySetting_Action_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingListEntrySetting_Action, UGameSettingListEntry_Setting, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingListEntrySetting_Action_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingListEntrySetting_Action)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_189_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESETTINGS_API UGameSettingListEntrySetting_Action(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingListEntrySetting_Action(UGameSettingListEntrySetting_Action&&) = delete; \
	UGameSettingListEntrySetting_Action(const UGameSettingListEntrySetting_Action&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingListEntrySetting_Action); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingListEntrySetting_Action); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameSettingListEntrySetting_Action) \
	GAMESETTINGS_API virtual ~UGameSettingListEntrySetting_Action();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_186_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_189_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_189_CALLBACK_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_189_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_189_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingListEntrySetting_Action;

// ********** End Class UGameSettingListEntrySetting_Action ****************************************

// ********** Begin Class UGameSettingListEntrySetting_Navigation **********************************
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_221_CALLBACK_WRAPPERS
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntrySetting_Navigation_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_221_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameSettingListEntrySetting_Navigation(); \
	friend struct Z_Construct_UClass_UGameSettingListEntrySetting_Navigation_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingListEntrySetting_Navigation_NoRegister(); \
public: \
	DECLARE_CLASS2(UGameSettingListEntrySetting_Navigation, UGameSettingListEntry_Setting, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/GameSettings"), Z_Construct_UClass_UGameSettingListEntrySetting_Navigation_NoRegister) \
	DECLARE_SERIALIZER(UGameSettingListEntrySetting_Navigation)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_221_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMESETTINGS_API UGameSettingListEntrySetting_Navigation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGameSettingListEntrySetting_Navigation(UGameSettingListEntrySetting_Navigation&&) = delete; \
	UGameSettingListEntrySetting_Navigation(const UGameSettingListEntrySetting_Navigation&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMESETTINGS_API, UGameSettingListEntrySetting_Navigation); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameSettingListEntrySetting_Navigation); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameSettingListEntrySetting_Navigation) \
	GAMESETTINGS_API virtual ~UGameSettingListEntrySetting_Navigation();


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_218_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_221_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_221_CALLBACK_WRAPPERS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_221_INCLASS_NO_PURE_DECLS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h_221_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGameSettingListEntrySetting_Navigation;

// ********** End Class UGameSettingListEntrySetting_Navigation ************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_Widgets_GameSettingListEntry_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
