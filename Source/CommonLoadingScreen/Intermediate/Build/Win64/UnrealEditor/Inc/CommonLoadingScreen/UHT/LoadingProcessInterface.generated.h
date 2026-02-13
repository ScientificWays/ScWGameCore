// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "LoadingProcessInterface.h"

#ifdef COMMONLOADINGSCREEN_LoadingProcessInterface_generated_h
#error "LoadingProcessInterface.generated.h already included, missing '#pragma once' in LoadingProcessInterface.h"
#endif
#define COMMONLOADINGSCREEN_LoadingProcessInterface_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Interface ULoadingProcessInterface *********************************************
COMMONLOADINGSCREEN_API UClass* Z_Construct_UClass_ULoadingProcessInterface_NoRegister();

#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	COMMONLOADINGSCREEN_API ULoadingProcessInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ULoadingProcessInterface(ULoadingProcessInterface&&) = delete; \
	ULoadingProcessInterface(const ULoadingProcessInterface&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(COMMONLOADINGSCREEN_API, ULoadingProcessInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULoadingProcessInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULoadingProcessInterface) \
	virtual ~ULoadingProcessInterface() = default;


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_16_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesULoadingProcessInterface(); \
	friend struct Z_Construct_UClass_ULoadingProcessInterface_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend COMMONLOADINGSCREEN_API UClass* Z_Construct_UClass_ULoadingProcessInterface_NoRegister(); \
public: \
	DECLARE_CLASS2(ULoadingProcessInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/CommonLoadingScreen"), Z_Construct_UClass_ULoadingProcessInterface_NoRegister) \
	DECLARE_SERIALIZER(ULoadingProcessInterface)


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_16_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_16_GENERATED_UINTERFACE_BODY() \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_16_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_16_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~ILoadingProcessInterface() {} \
public: \
	typedef ULoadingProcessInterface UClassType; \
	typedef ILoadingProcessInterface ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_13_PROLOG
#define FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h_16_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ULoadingProcessInterface;

// ********** End Interface ULoadingProcessInterface ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_zanayn_Documents_GitHub_lyra_Plugins_CommonLoadingScreen_Source_CommonLoadingScreen_Public_LoadingProcessInterface_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
