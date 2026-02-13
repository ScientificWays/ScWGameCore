// Scientific Ways

#include "Character/ScWCharacterCapsule.h"

#include "AbilitySystem/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

UScWCharacterCapsule::UScWCharacterCapsule()
{
	TagCollisionProfileNameMap = {
		{ FScWCoreTags::Collision_None, UCollisionProfile::NoCollision_ProfileName },
	};
}

//~ Begin Initialize
void UScWCharacterCapsule::InitFromASC(UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) // IScWASC_InitInterface
{
	ensureReturn(InInitASC);
	//ensureReturn(InOwnerActor);
	//ensureReturn(InAvatarActor);

	for (auto SampleTagProfile : TagCollisionProfileNameMap)
	{
		InInitASC->RegisterGameplayTagEvent(SampleTagProfile.Key, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnCollisionTagNumChanged);
	}
	//UpdateCollisionProfileFromTags();
}

void UScWCharacterCapsule::BeginPlay() // UActorComponent
{
	DefaultCollisionProfileName = GetCollisionProfileName();
	UpdateCollisionProfileFromTags();

	Super::BeginPlay();
}
//~ End Initialize

//~ Begin Tags
void UScWCharacterCapsule::OnCollisionTagNumChanged(const FGameplayTag InCallbackTag, int32 InNewNum)
{
	UpdateCollisionProfileFromTags();
}

void UScWCharacterCapsule::UpdateCollisionProfileFromTags()
{
	UScWAbilitySystemComponent* InitASC = GetInitASC();
	ensureReturn(InitASC);

	for (auto SampleTagProfile : TagCollisionProfileNameMap)
	{
		if (InitASC->HasMatchingGameplayTag(SampleTagProfile.Key))
		{
			SetCollisionProfileName(SampleTagProfile.Value);
			return;
		}
	}
	SetCollisionProfileName(DefaultCollisionProfileName);
}
//~ End Tags
