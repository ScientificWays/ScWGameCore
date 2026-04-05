// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "AbilitySystem/ScWASC_InitInterface.h"

#include "ScWCharacterCapsule.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *	Custom capsule component for ScW characters that switches collision profiles based on gameplay tags
 *	and initializes from the ability system.
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Character Capsule (Component)"))
class UScWCharacterCapsule : public UCapsuleComponent, public IScWASC_InitInterface
{
	GENERATED_BODY()
	
public:	
	
	UScWCharacterCapsule();
	
//~ Begin Initialize
public:
	virtual void InitFromASC(class UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) override; // IScWASC_InitInterface
protected:
	virtual void BeginPlay() override; // UActorComponent
//~ End Initialize

//~ Begin Profiles
public:

	UPROPERTY(Category = "Profiles", EditAnywhere, BlueprintReadWrite, meta = (Categories = "Collision"))
	TMap<FGameplayTag, FCollisionProfileName> TagCollisionProfileNameMap;

	UPROPERTY(Transient)
	FName DefaultCollisionProfileName;
//~ End Profiles

//~ Begin Tags
protected:
	void OnCollisionTagNumChanged(const FGameplayTag InCallbackTag, int32 InNewCount);
	void UpdateCollisionProfileFromTags();
//~ End Tags
};

#undef MODULE_API
