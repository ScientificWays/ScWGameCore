// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "AbilitySystem/ScWAbilitySet.h"

#include "Character/ScWPawnDataFragment.h"

#include "ScWPawnDataFragment_AbilitySets.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *
 */
UCLASS(MinimalAPI, Blueprintable, BlueprintType, meta = (DisplayName = "[ScW] Pawn Data Fragment (Ability Sets)"))
class UScWPawnDataFragment_AbilitySets : public UScWPawnDataFragment
{
	GENERATED_BODY()

//~ Begin Initialize
public:
	MODULE_API UScWPawnDataFragment_AbilitySets();
protected:
	MODULE_API virtual void BP_InitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const override; // UScWPawnDataFragment
	MODULE_API virtual void BP_UninitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const override; // UScWPawnDataFragment
//~ End Initialize
	
//~ Begin Ability Sets
public:

	UPROPERTY(Category = "Ability Sets", EditDefaultsOnly, BlueprintReadOnly)
	TArray<TObjectPtr<const UScWAbilitySet>> AbilitySetsToGrant;

protected:

	// Authority-only list of granted handles
	UPROPERTY()
	mutable TMap<TObjectPtr<UScWPawnExtensionComponent>, FScWAbilitySet_GrantedHandles> PerPawnGrantedHandles;
//~ End Ability Sets
};

#undef MODULE_API
