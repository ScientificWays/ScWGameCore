// Scientific Ways

#pragma once

#include "Engine/DataAsset.h"

#include "ScWPawnData.generated.h"

#define MODULE_API SCWGAMECORE_API

class APawn;
class UScWAbilitySet;
class UScWAbilityTagRelationshipMapping;
//class UScWCameraMode;
class UScWInputConfig;
class UObject;


/**
 * UScWPawnData
 *
 *	Non-mutable data asset that contains properties used to define a pawn.
 */
UCLASS(MinimalAPI, BlueprintType, Const, Meta = (DisplayName = "[ScW] Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class UScWPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	MODULE_API UScWPawnData(const FObjectInitializer& ObjectInitializer);

public:

	// Class to instantiate for this pawn (should usually derive from AScWPawn or AScWCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ScW | Pawn")
	TSubclassOf<APawn> PawnClass;

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ScW | Abilities")
	TArray<TObjectPtr<UScWAbilitySet>> AbilitySets;

	// What mapping of ability tags to use for actions taking by this pawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ScW | Abilities")
	TObjectPtr<UScWAbilityTagRelationshipMapping> TagRelationshipMapping;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ScW | Input")
	TObjectPtr<UScWInputConfig> InputConfig;

	// Default camera mode used by player controlled pawns.
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ScW | Camera")
	//TSubclassOf<UScWCameraMode> DefaultCameraMode;
};

#undef MODULE_API
