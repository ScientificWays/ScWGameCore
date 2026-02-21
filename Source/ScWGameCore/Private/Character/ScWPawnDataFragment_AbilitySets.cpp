// Scientific Ways

#include "Character/ScWPawnDataFragment_AbilitySets.h"

#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "Character/ScWPawnExtensionComponent.h"

//~ Begin Initialize
UScWPawnDataFragment_AbilitySets::UScWPawnDataFragment_AbilitySets()
{
	
}

void UScWPawnDataFragment_AbilitySets::BP_InitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const // UScWPawnDataFragment
{
	ensureReturn(InPawnExtComponent);

	UScWAbilitySystemComponent* PawnASC = InPawnExtComponent->GetScWAbilitySystemComponent();
	ensureReturn(PawnASC);

	FScWAbilitySet_GrantedHandles GrantedHandles;
	for (const auto& AbilitySet : AbilitySetsToGrant)
	{
		AbilitySet->GiveToAbilitySystem(PawnASC, &GrantedHandles, const_cast<UScWPawnDataFragment_AbilitySets*>(this));
	}
}

void UScWPawnDataFragment_AbilitySets::BP_UninitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const // UScWPawnDataFragment
{
	ensureReturn(InPawnExtComponent);

	if (PerPawnGrantedHandles.Contains(InPawnExtComponent))
	{
		UScWAbilitySystemComponent* PawnASC = InPawnExtComponent->GetScWAbilitySystemComponent();
		ensureReturn(PawnASC);

		FScWAbilitySet_GrantedHandles GrantedHandles = PerPawnGrantedHandles[InPawnExtComponent];
		GrantedHandles.TakeFromAbilitySystem(PawnASC);

		PerPawnGrantedHandles.Remove(InPawnExtComponent);
	}
}
//~ End Initialize
