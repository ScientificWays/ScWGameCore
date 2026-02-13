// Scientific Ways

#include "Character/ScWCharacterMesh_Base.h"

#include "Animation/ScWAnimInstance_Base.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

UScWCharacterMesh_Base::UScWCharacterMesh_Base()
{
	
}

//~ Begin Initialize
void UScWCharacterMesh_Base::OnRegister() // UActorComponent
{
	Super::OnRegister();

	
}

void UScWCharacterMesh_Base::BeginPlay() // UActorComponent
{
	Super::BeginPlay();

	
}

void UScWCharacterMesh_Base::InitFromASC(UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) // IScWASC_InitInterface
{
	ensureReturn(InInitASC);
	//ensureReturn(InOwnerActor);
	//ensureReturn(InAvatarActor);

	if (UScWAnimInstance_Base* AnimInstance = Cast<UScWAnimInstance_Base>(GetAnimInstance()))
	{
		AnimInstance->InitializeFromOwnerAbilitySystem(InInitASC);
	}
}
//~ End Initialize
