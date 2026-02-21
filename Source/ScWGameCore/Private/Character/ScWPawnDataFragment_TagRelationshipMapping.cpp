// Scientific Ways

#include "Character/ScWPawnDataFragment_TagRelationshipMapping.h"

#include "Character/ScWPawnExtensionComponent.h"

//~ Begin Initialize
UScWPawnDataFragment_TagRelationshipMapping::UScWPawnDataFragment_TagRelationshipMapping()
{
	
}

void UScWPawnDataFragment_TagRelationshipMapping::BP_InitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const // UScWPawnDataFragment
{
	ensureReturn(InPawnExtComponent);

	UScWAbilitySystemComponent* PawnASC = InPawnExtComponent->GetScWAbilitySystemComponent();
	ensureReturn(PawnASC);
	PawnASC->SetTagRelationshipMapping(TagRelationshipMapping);
}

void UScWPawnDataFragment_TagRelationshipMapping::BP_UninitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const // UScWPawnDataFragment
{
	ensureReturn(InPawnExtComponent);

	UScWAbilitySystemComponent* PawnASC = InPawnExtComponent->GetScWAbilitySystemComponent();
	ensureReturn(PawnASC);
	PawnASC->SetTagRelationshipMapping(nullptr);
}
//~ End Initialize
