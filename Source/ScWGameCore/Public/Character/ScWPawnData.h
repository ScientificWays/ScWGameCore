// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWPawnData.generated.h"

#define MODULE_API SCWGAMECORE_API

class APawn;
class UScWAbilitySet;
class UScWAbilityTagRelationshipMapping;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Data | Pawn")
	TSubclassOf<APawn> PawnClass;

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Data | Abilities")
	TArray<TObjectPtr<UScWAbilitySet>> AbilitySets;

	// What mapping of ability tags to use for actions taking by this pawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Data | Abilities")
	TObjectPtr<UScWAbilityTagRelationshipMapping> TagRelationshipMapping;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Data | Input")
	TObjectPtr<UScWInputConfig> InputConfig;

	// Default camera mode used by player controlled pawns.
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Data | Camera")
	//TSubclassOf<UScWCameraMode> DefaultCameraMode;
};

#undef MODULE_API
