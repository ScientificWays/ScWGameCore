// Scientific Ways

#pragma once

#include "CoreMinimal.h"

#include "Logging/LogMacros.h"

#define ATTRIBUTE_ACCESSORS(InClass, InProperty)							\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(InClass, InProperty)					\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(InProperty)								\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(InProperty)								\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(InProperty)

#define GET_ROUNDED_VECTOR_STRING(InV) FString::Printf(TEXT("X=%d,Y=%d,Z=%d"), FMath::RoundToInt(InV.Z), FMath::RoundToInt(InV.Y), FMath::RoundToInt(InV.Z))

#define CONSTRUCTOR_TRY_LOAD_OBJECT(InClass, InProperty, InPath) \
	{ \
		static ConstructorHelpers::FObjectFinder<InClass> LoadedAsset(TEXT(InPath)); \
		if (LoadedAsset.Succeeded()) \
		{ \
			InProperty = LoadedAsset.Object; \
		} \
	}

#define CONSTRUCTOR_TRY_LOAD_CLASS(InClass, InProperty, InPath) \
	{ \
		static ConstructorHelpers::FClassFinder<InClass> LoadedAsset(TEXT(InPath)); \
		if (LoadedAsset.Succeeded()) \
		{ \
			InProperty = LoadedAsset.Class; \
		} \
	}

#define ensureContinue(InCondition) ensure(InCondition); if (!(InCondition)) continue;
#define ensureBreak(InCondition) ensure(InCondition); if (!(InCondition)) break;
#define ensureIf(InCondition) ensure(InCondition); if (InCondition)
#define ensureReturn(InCondition, ...) ensure(InCondition); if (!(InCondition)) return __VA_ARGS__;
#define ensureGoto(InCondition, InLabel) ensure(InCondition); if (!(InCondition)) goto InLabel;

#define IS_EDITOR_WORLD(...) (WITH_EDITOR && ((__VA_ARGS__ GetWorld()) && (__VA_ARGS__ GetWorld()->WorldType == EWorldType::Editor))) // Common check with compile-time optimization for non-editor builds

#define TraceTypeQuery_Visibility				ETraceTypeQuery::TraceTypeQuery1
#define TraceTypeQuery_Camera					ETraceTypeQuery::TraceTypeQuery2
#define TraceTypeQuery_Melee					ETraceTypeQuery::TraceTypeQuery3
#define TraceTypeQuery_Interact					ETraceTypeQuery::TraceTypeQuery4

#define CollisionChannel_Visibility				ECollisionChannel::ECC_GameTraceChannel1
#define CollisionChannel_Camera					ECollisionChannel::ECC_GameTraceChannel2
#define CollisionChannel_Melee					ECollisionChannel::ECC_GameTraceChannel3

//#define ECC_Shoot								ECollisionChannel::ECC_GameTraceChannel1
//#define ECC_Interact							ECollisionChannel::ECC_GameTraceChannel2
//#define ECC_OnlyCharacterIgnore				ECollisionChannel::ECC_GameTraceChannel5
//#define ECC_OverlapAllShapes					ECollisionChannel::ECC_GameTraceChannel10

#define ObjectTypeQuery_WorldStatic				EObjectTypeQuery::ObjectTypeQuery1
#define ObjectTypeQuery_WorldDynamic			EObjectTypeQuery::ObjectTypeQuery2
#define ObjectTypeQuery_Pawn					EObjectTypeQuery::ObjectTypeQuery3
#define ObjectTypeQuery_PhysicsBody				EObjectTypeQuery::ObjectTypeQuery4
#define ObjectTypeQuery_Vehicle					EObjectTypeQuery::ObjectTypeQuery5
#define ObjectTypeQuery_Destructible			EObjectTypeQuery::ObjectTypeQuery6
//#define ObjectTypeQuery_PawnA					EObjectTypeQuery::ObjectTypeQuery7
//#define ObjectTypeQuery_PawnB					EObjectTypeQuery::ObjectTypeQuery8
//#define ObjectTypeQuery_Building				EObjectTypeQuery::ObjectTypeQuery9
//#define ObjectTypeQuery_Driver				EObjectTypeQuery::ObjectTypeQuery10
//#define ObjectTypeQuery_Volume				EObjectTypeQuery::ObjectTypeQuery11

FString GetClientServerContextString(UObject* InContext = nullptr);

namespace FScWMath
{
	FORCEINLINE FIntVector MinIntVector(const FIntVector& InA, const FIntVector& InB)
	{
		return FIntVector(FMath::Min(InA.X, InB.X), FMath::Min(InA.Y, InB.Y), FMath::Min(InA.Z, InB.Z));
	}

	FORCEINLINE FIntVector MaxIntVector(const FIntVector& InA, const FIntVector& InB)
	{
		return FIntVector(FMath::Max(InA.X, InB.X), FMath::Max(InA.Y, InB.Y), FMath::Max(InA.Z, InB.Z));
	}

	FORCEINLINE FIntVector ClampIntVector(const FIntVector& InVector, const FIntVector& InMin, const FIntVector& InMax)
	{
		return FIntVector(FMath::Clamp(InVector.X, InMin.X, InMax.X), FMath::Clamp(InVector.Y, InMin.Y, InMax.Y), FMath::Clamp(InVector.Z, InMin.Z, InMax.Z));
	}
}
