// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameSettingValueScalar.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeGameSettingValueScalar() {}

// ********** Begin Cross Module References ********************************************************
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValue();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueScalar();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueScalar_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameSettings();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UGameSettingValueScalar **************************************************
void UGameSettingValueScalar::StaticRegisterNativesUGameSettingValueScalar()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGameSettingValueScalar;
UClass* UGameSettingValueScalar::GetPrivateStaticClass()
{
	using TClass = UGameSettingValueScalar;
	if (!Z_Registration_Info_UClass_UGameSettingValueScalar.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameSettingValueScalar"),
			Z_Registration_Info_UClass_UGameSettingValueScalar.InnerSingleton,
			StaticRegisterNativesUGameSettingValueScalar,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UGameSettingValueScalar.InnerSingleton;
}
UClass* Z_Construct_UClass_UGameSettingValueScalar_NoRegister()
{
	return UGameSettingValueScalar::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGameSettingValueScalar_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "GameSettingValueScalar.h" },
		{ "ModuleRelativePath", "Public/GameSettingValueScalar.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameSettingValueScalar>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGameSettingValueScalar_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameSettingValue,
	(UObject* (*)())Z_Construct_UPackage__Script_GameSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueScalar_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameSettingValueScalar_Statics::ClassParams = {
	&UGameSettingValueScalar::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000800A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueScalar_Statics::Class_MetaDataParams), Z_Construct_UClass_UGameSettingValueScalar_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGameSettingValueScalar()
{
	if (!Z_Registration_Info_UClass_UGameSettingValueScalar.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameSettingValueScalar.OuterSingleton, Z_Construct_UClass_UGameSettingValueScalar_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGameSettingValueScalar.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGameSettingValueScalar);
UGameSettingValueScalar::~UGameSettingValueScalar() {}
// ********** End Class UGameSettingValueScalar ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueScalar_h__Script_GameSettings_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGameSettingValueScalar, UGameSettingValueScalar::StaticClass, TEXT("UGameSettingValueScalar"), &Z_Registration_Info_UClass_UGameSettingValueScalar, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameSettingValueScalar), 2421394190U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueScalar_h__Script_GameSettings_1345053744(TEXT("/Script/GameSettings"),
	Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueScalar_h__Script_GameSettings_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueScalar_h__Script_GameSettings_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
