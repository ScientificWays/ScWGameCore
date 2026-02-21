// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Character/ScWPawnDataFragment.h"

#include "ScWPawnDataFragment_TagRelationshipMapping.generated.h"

#define MODULE_API SCWGAMECORE_API

class UScWAbilityTagRelationshipMapping;

/**
 *
 */
UCLASS(MinimalAPI, Blueprintable, BlueprintType, meta = (DisplayName = "[ScW] Pawn Data Fragment (Tag Relationship Mapping)"))
class UScWPawnDataFragment_TagRelationshipMapping : public UScWPawnDataFragment
{
	GENERATED_BODY()

//~ Begin Initialize
public:
	MODULE_API UScWPawnDataFragment_TagRelationshipMapping();
protected:
	MODULE_API virtual void BP_InitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const override; // UScWPawnDataFragment
	MODULE_API virtual void BP_UninitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const override; // UScWPawnDataFragment
//~ End Initialize
	
//~ Begin Ability System
public:

	// What mapping of ability tags to use for actions taking by this pawn
	UPROPERTY(Category = "Ability System", EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UScWAbilityTagRelationshipMapping> TagRelationshipMapping;
//~ End Ability System
};

#undef MODULE_API
