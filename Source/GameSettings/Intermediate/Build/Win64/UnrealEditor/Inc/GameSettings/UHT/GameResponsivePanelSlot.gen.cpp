// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Widgets/Responsive/GameResponsivePanelSlot.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeGameResponsivePanelSlot() {}

// ********** Begin Cross Module References ********************************************************
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameResponsivePanelSlot();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameResponsivePanelSlot_NoRegister();
UMG_API UClass* Z_Construct_UClass_UPanelSlot();
UPackage* Z_Construct_UPackage__Script_GameSettings();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UGameResponsivePanelSlot *************************************************
void UGameResponsivePanelSlot::StaticRegisterNativesUGameResponsivePanelSlot()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGameResponsivePanelSlot;
UClass* UGameResponsivePanelSlot::GetPrivateStaticClass()
{
	using TClass = UGameResponsivePanelSlot;
	if (!Z_Registration_Info_UClass_UGameResponsivePanelSlot.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameResponsivePanelSlot"),
			Z_Registration_Info_UClass_UGameResponsivePanelSlot.InnerSingleton,
			StaticRegisterNativesUGameResponsivePanelSlot,
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
	return Z_Registration_Info_UClass_UGameResponsivePanelSlot.InnerSingleton;
}
UClass* Z_Construct_UClass_UGameResponsivePanelSlot_NoRegister()
{
	return UGameResponsivePanelSlot::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGameResponsivePanelSlot_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Widgets/Responsive/GameResponsivePanelSlot.h" },
		{ "ModuleRelativePath", "Private/Widgets/Responsive/GameResponsivePanelSlot.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameResponsivePanelSlot>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGameResponsivePanelSlot_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPanelSlot,
	(UObject* (*)())Z_Construct_UPackage__Script_GameSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGameResponsivePanelSlot_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameResponsivePanelSlot_Statics::ClassParams = {
	&UGameResponsivePanelSlot::StaticClass,
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
	0x00A000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGameResponsivePanelSlot_Statics::Class_MetaDataParams), Z_Construct_UClass_UGameResponsivePanelSlot_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGameResponsivePanelSlot()
{
	if (!Z_Registration_Info_UClass_UGameResponsivePanelSlot.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameResponsivePanelSlot.OuterSingleton, Z_Construct_UClass_UGameResponsivePanelSlot_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGameResponsivePanelSlot.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGameResponsivePanelSlot);
UGameResponsivePanelSlot::~UGameResponsivePanelSlot() {}
// ********** End Class UGameResponsivePanelSlot ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanelSlot_h__Script_GameSettings_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGameResponsivePanelSlot, UGameResponsivePanelSlot::StaticClass, TEXT("UGameResponsivePanelSlot"), &Z_Registration_Info_UClass_UGameResponsivePanelSlot, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameResponsivePanelSlot), 2986175472U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanelSlot_h__Script_GameSettings_3806925617(TEXT("/Script/GameSettings"),
	Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanelSlot_h__Script_GameSettings_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Private_Widgets_Responsive_GameResponsivePanelSlot_h__Script_GameSettings_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
