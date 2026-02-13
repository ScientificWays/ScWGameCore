// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameSettingValueDiscreteDynamic.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeGameSettingValueDiscreteDynamic() {}

// ********** Begin Cross Module References ********************************************************
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscrete();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_NoRegister();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_NoRegister();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_NoRegister();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_NoRegister();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_NoRegister();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D();
GAMESETTINGS_API UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameSettings();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UGameSettingValueDiscreteDynamic *****************************************
void UGameSettingValueDiscreteDynamic::StaticRegisterNativesUGameSettingValueDiscreteDynamic()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic;
UClass* UGameSettingValueDiscreteDynamic::GetPrivateStaticClass()
{
	using TClass = UGameSettingValueDiscreteDynamic;
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameSettingValueDiscreteDynamic"),
			Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic.InnerSingleton,
			StaticRegisterNativesUGameSettingValueDiscreteDynamic,
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
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic.InnerSingleton;
}
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_NoRegister()
{
	return UGameSettingValueDiscreteDynamic::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//////////////////////////////////////////////////////////////////////////\n// UGameSettingValueDiscreteDynamic\n//////////////////////////////////////////////////////////////////////////\n" },
#endif
		{ "IncludePath", "GameSettingValueDiscreteDynamic.h" },
		{ "ModuleRelativePath", "Public/GameSettingValueDiscreteDynamic.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UGameSettingValueDiscreteDynamic" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameSettingValueDiscreteDynamic>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameSettingValueDiscrete,
	(UObject* (*)())Z_Construct_UPackage__Script_GameSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Statics::ClassParams = {
	&UGameSettingValueDiscreteDynamic::StaticClass,
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
	0x000800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Statics::Class_MetaDataParams), Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic()
{
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic.OuterSingleton, Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGameSettingValueDiscreteDynamic);
UGameSettingValueDiscreteDynamic::~UGameSettingValueDiscreteDynamic() {}
// ********** End Class UGameSettingValueDiscreteDynamic *******************************************

// ********** Begin Class UGameSettingValueDiscreteDynamic_Bool ************************************
void UGameSettingValueDiscreteDynamic_Bool::StaticRegisterNativesUGameSettingValueDiscreteDynamic_Bool()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Bool;
UClass* UGameSettingValueDiscreteDynamic_Bool::GetPrivateStaticClass()
{
	using TClass = UGameSettingValueDiscreteDynamic_Bool;
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Bool.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameSettingValueDiscreteDynamic_Bool"),
			Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Bool.InnerSingleton,
			StaticRegisterNativesUGameSettingValueDiscreteDynamic_Bool,
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
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Bool.InnerSingleton;
}
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_NoRegister()
{
	return UGameSettingValueDiscreteDynamic_Bool::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//////////////////////////////////////////////////////////////////////////\n// UGameSettingValueDiscreteDynamic_Bool\n//////////////////////////////////////////////////////////////////////////\n" },
#endif
		{ "IncludePath", "GameSettingValueDiscreteDynamic.h" },
		{ "ModuleRelativePath", "Public/GameSettingValueDiscreteDynamic.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UGameSettingValueDiscreteDynamic_Bool" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameSettingValueDiscreteDynamic_Bool>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameSettingValueDiscreteDynamic,
	(UObject* (*)())Z_Construct_UPackage__Script_GameSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_Statics::ClassParams = {
	&UGameSettingValueDiscreteDynamic_Bool::StaticClass,
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
	0x000800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_Statics::Class_MetaDataParams), Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool()
{
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Bool.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Bool.OuterSingleton, Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Bool.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGameSettingValueDiscreteDynamic_Bool);
UGameSettingValueDiscreteDynamic_Bool::~UGameSettingValueDiscreteDynamic_Bool() {}
// ********** End Class UGameSettingValueDiscreteDynamic_Bool **************************************

// ********** Begin Class UGameSettingValueDiscreteDynamic_Number **********************************
void UGameSettingValueDiscreteDynamic_Number::StaticRegisterNativesUGameSettingValueDiscreteDynamic_Number()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Number;
UClass* UGameSettingValueDiscreteDynamic_Number::GetPrivateStaticClass()
{
	using TClass = UGameSettingValueDiscreteDynamic_Number;
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Number.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameSettingValueDiscreteDynamic_Number"),
			Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Number.InnerSingleton,
			StaticRegisterNativesUGameSettingValueDiscreteDynamic_Number,
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
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Number.InnerSingleton;
}
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_NoRegister()
{
	return UGameSettingValueDiscreteDynamic_Number::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//////////////////////////////////////////////////////////////////////////\n// UGameSettingValueDiscreteDynamic_Number\n//////////////////////////////////////////////////////////////////////////\n" },
#endif
		{ "IncludePath", "GameSettingValueDiscreteDynamic.h" },
		{ "ModuleRelativePath", "Public/GameSettingValueDiscreteDynamic.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UGameSettingValueDiscreteDynamic_Number" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameSettingValueDiscreteDynamic_Number>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameSettingValueDiscreteDynamic,
	(UObject* (*)())Z_Construct_UPackage__Script_GameSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_Statics::ClassParams = {
	&UGameSettingValueDiscreteDynamic_Number::StaticClass,
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
	0x000800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_Statics::Class_MetaDataParams), Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number()
{
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Number.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Number.OuterSingleton, Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Number.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGameSettingValueDiscreteDynamic_Number);
UGameSettingValueDiscreteDynamic_Number::~UGameSettingValueDiscreteDynamic_Number() {}
// ********** End Class UGameSettingValueDiscreteDynamic_Number ************************************

// ********** Begin Class UGameSettingValueDiscreteDynamic_Enum ************************************
void UGameSettingValueDiscreteDynamic_Enum::StaticRegisterNativesUGameSettingValueDiscreteDynamic_Enum()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Enum;
UClass* UGameSettingValueDiscreteDynamic_Enum::GetPrivateStaticClass()
{
	using TClass = UGameSettingValueDiscreteDynamic_Enum;
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Enum.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameSettingValueDiscreteDynamic_Enum"),
			Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Enum.InnerSingleton,
			StaticRegisterNativesUGameSettingValueDiscreteDynamic_Enum,
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
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Enum.InnerSingleton;
}
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_NoRegister()
{
	return UGameSettingValueDiscreteDynamic_Enum::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//////////////////////////////////////////////////////////////////////////\n// UGameSettingValueDiscreteDynamic_Enum\n//////////////////////////////////////////////////////////////////////////\n" },
#endif
		{ "IncludePath", "GameSettingValueDiscreteDynamic.h" },
		{ "ModuleRelativePath", "Public/GameSettingValueDiscreteDynamic.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UGameSettingValueDiscreteDynamic_Enum" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameSettingValueDiscreteDynamic_Enum>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameSettingValueDiscreteDynamic,
	(UObject* (*)())Z_Construct_UPackage__Script_GameSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_Statics::ClassParams = {
	&UGameSettingValueDiscreteDynamic_Enum::StaticClass,
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
	0x000800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_Statics::Class_MetaDataParams), Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum()
{
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Enum.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Enum.OuterSingleton, Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Enum.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGameSettingValueDiscreteDynamic_Enum);
UGameSettingValueDiscreteDynamic_Enum::~UGameSettingValueDiscreteDynamic_Enum() {}
// ********** End Class UGameSettingValueDiscreteDynamic_Enum **************************************

// ********** Begin Class UGameSettingValueDiscreteDynamic_Color ***********************************
void UGameSettingValueDiscreteDynamic_Color::StaticRegisterNativesUGameSettingValueDiscreteDynamic_Color()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Color;
UClass* UGameSettingValueDiscreteDynamic_Color::GetPrivateStaticClass()
{
	using TClass = UGameSettingValueDiscreteDynamic_Color;
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Color.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameSettingValueDiscreteDynamic_Color"),
			Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Color.InnerSingleton,
			StaticRegisterNativesUGameSettingValueDiscreteDynamic_Color,
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
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Color.InnerSingleton;
}
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_NoRegister()
{
	return UGameSettingValueDiscreteDynamic_Color::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//////////////////////////////////////////////////////////////////////////\n// UGameSettingValueDiscreteDynamic_Color\n//////////////////////////////////////////////////////////////////////////\n" },
#endif
		{ "IncludePath", "GameSettingValueDiscreteDynamic.h" },
		{ "ModuleRelativePath", "Public/GameSettingValueDiscreteDynamic.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UGameSettingValueDiscreteDynamic_Color" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameSettingValueDiscreteDynamic_Color>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameSettingValueDiscreteDynamic,
	(UObject* (*)())Z_Construct_UPackage__Script_GameSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_Statics::ClassParams = {
	&UGameSettingValueDiscreteDynamic_Color::StaticClass,
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
	0x000800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_Statics::Class_MetaDataParams), Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color()
{
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Color.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Color.OuterSingleton, Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Color.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGameSettingValueDiscreteDynamic_Color);
UGameSettingValueDiscreteDynamic_Color::~UGameSettingValueDiscreteDynamic_Color() {}
// ********** End Class UGameSettingValueDiscreteDynamic_Color *************************************

// ********** Begin Class UGameSettingValueDiscreteDynamic_Vector2D ********************************
void UGameSettingValueDiscreteDynamic_Vector2D::StaticRegisterNativesUGameSettingValueDiscreteDynamic_Vector2D()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Vector2D;
UClass* UGameSettingValueDiscreteDynamic_Vector2D::GetPrivateStaticClass()
{
	using TClass = UGameSettingValueDiscreteDynamic_Vector2D;
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Vector2D.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GameSettingValueDiscreteDynamic_Vector2D"),
			Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Vector2D.InnerSingleton,
			StaticRegisterNativesUGameSettingValueDiscreteDynamic_Vector2D,
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
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Vector2D.InnerSingleton;
}
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_NoRegister()
{
	return UGameSettingValueDiscreteDynamic_Vector2D::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//////////////////////////////////////////////////////////////////////////\n// UGameSettingValueDiscreteDynamic_Vector2D\n//////////////////////////////////////////////////////////////////////////\n" },
#endif
		{ "IncludePath", "GameSettingValueDiscreteDynamic.h" },
		{ "ModuleRelativePath", "Public/GameSettingValueDiscreteDynamic.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UGameSettingValueDiscreteDynamic_Vector2D" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameSettingValueDiscreteDynamic_Vector2D>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameSettingValueDiscreteDynamic,
	(UObject* (*)())Z_Construct_UPackage__Script_GameSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_Statics::ClassParams = {
	&UGameSettingValueDiscreteDynamic_Vector2D::StaticClass,
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
	0x000800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_Statics::Class_MetaDataParams), Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D()
{
	if (!Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Vector2D.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Vector2D.OuterSingleton, Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Vector2D.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGameSettingValueDiscreteDynamic_Vector2D);
UGameSettingValueDiscreteDynamic_Vector2D::~UGameSettingValueDiscreteDynamic_Vector2D() {}
// ********** End Class UGameSettingValueDiscreteDynamic_Vector2D **********************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscreteDynamic_h__Script_GameSettings_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGameSettingValueDiscreteDynamic, UGameSettingValueDiscreteDynamic::StaticClass, TEXT("UGameSettingValueDiscreteDynamic"), &Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameSettingValueDiscreteDynamic), 4281866483U) },
		{ Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Bool, UGameSettingValueDiscreteDynamic_Bool::StaticClass, TEXT("UGameSettingValueDiscreteDynamic_Bool"), &Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Bool, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameSettingValueDiscreteDynamic_Bool), 3438705592U) },
		{ Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Number, UGameSettingValueDiscreteDynamic_Number::StaticClass, TEXT("UGameSettingValueDiscreteDynamic_Number"), &Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Number, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameSettingValueDiscreteDynamic_Number), 2019069166U) },
		{ Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Enum, UGameSettingValueDiscreteDynamic_Enum::StaticClass, TEXT("UGameSettingValueDiscreteDynamic_Enum"), &Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Enum, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameSettingValueDiscreteDynamic_Enum), 1856083133U) },
		{ Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Color, UGameSettingValueDiscreteDynamic_Color::StaticClass, TEXT("UGameSettingValueDiscreteDynamic_Color"), &Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Color, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameSettingValueDiscreteDynamic_Color), 3569973062U) },
		{ Z_Construct_UClass_UGameSettingValueDiscreteDynamic_Vector2D, UGameSettingValueDiscreteDynamic_Vector2D::StaticClass, TEXT("UGameSettingValueDiscreteDynamic_Vector2D"), &Z_Registration_Info_UClass_UGameSettingValueDiscreteDynamic_Vector2D, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameSettingValueDiscreteDynamic_Vector2D), 137334323U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscreteDynamic_h__Script_GameSettings_3730089496(TEXT("/Script/GameSettings"),
	Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscreteDynamic_h__Script_GameSettings_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_zanayn_Documents_GitHub_lyra_Plugins_GameSettings_Source_Public_GameSettingValueDiscreteDynamic_h__Script_GameSettings_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
