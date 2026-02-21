// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWPawnData.generated.h"

#define MODULE_API SCWGAMECORE_API

class APawn;
class UScWPawnDataFragment;
class UScWPawnExtensionComponent;
//class UScWCameraMode;
class UScWInputConfig;
class UObject;

/**
 *	Non-mutable data asset that contains properties used to define a pawn.
 */
UCLASS(MinimalAPI, BlueprintType, Const, Meta = (DisplayName = "[ScW] Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class UScWPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	static MODULE_API const FName NAME_PawnDataInitialized;
	static MODULE_API const FName NAME_PawnDataUninitialized;

	MODULE_API UScWPawnData(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Category = "Spawning", BlueprintCallable, BlueprintPure = "false", meta = (WorldContext = "InWCO", KeyWords = "SpawnActor, CreateActor, CreatePawn"))
	MODULE_API APawn* SpawnPawnActorAndInitWithPawnData(
		const UObject* InWCO,
		const FTransform& InTransform,
		AActor* InOwner = nullptr,
		APawn* InInstigator = nullptr,
		ESpawnActorCollisionHandlingMethod InCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined,
		ESpawnActorScaleMethod InTransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot
	) const;

public:

	// Class to instantiate for this pawn (should usually derive from AScWPawn or AScWCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Data")
	TSubclassOf<APawn> PawnClass;

	UFUNCTION(Category = "Pawn Data", BlueprintCallable, meta = (DeterminesOutputType = "InTypeClass"))
	const UScWPawnDataFragment* GetFragmentByClass(TSubclassOf<UScWPawnDataFragment> InTypeClass) const;

	template<class T>
	const T* GetFragmentByClass() const
	{
		return Cast<T>(GetFragmentByClass(T::StaticClass()));
	}

	void InitializePawn(UScWPawnExtensionComponent* InPawnExtComponent) const;
	void UninitializePawn(UScWPawnExtensionComponent* InPawnExtComponent) const;

	// Actors to spawn on the pawn when this is equipped
	UPROPERTY(Category = "Pawn Data", EditDefaultsOnly, Instanced)
	TArray<TObjectPtr<const UScWPawnDataFragment>> Fragments;

	// Default camera mode used by player controlled pawns.
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Data | Camera")
	//TSubclassOf<UScWCameraMode> DefaultCameraMode;
};

#undef MODULE_API
