// Scientific Ways

#include "Character/ScWCharacterMesh_ThirdPerson.h"

#include "Animation/ScWAnimInstance_ThirdPerson.h"
#include "Animation/ScWAnimationsFunctionLibrary.h"

#include "AbilitySystem/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/ScWAS_CharacterMovement.h"

#include "Damage/ScWDamageType.h"
#include "Damage/ScWAttributeHealthComponent.h"

UScWCharacterMesh_ThirdPerson::UScWCharacterMesh_ThirdPerson()
{
	FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;
	VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	RagdollCollisionProfileName = TEXT("Ragdoll");
}

//~ Begin Initialize
void UScWCharacterMesh_ThirdPerson::BeginPlay() // UActorComponent
{
	Super::BeginPlay();

	AActor* OwnerActor = GetOwner();
	ensureReturn(OwnerActor);

	if (UScWAttributeHealthComponent* HealthComponent = OwnerActor->GetComponentByClass<UScWAttributeHealthComponent>())
	{
		HealthComponent->OnDamageApplied.AddDynamic(this, &ThisClass::HandleDamageApplied);
		HealthComponent->OnDied.AddDynamic(this, &ThisClass::HandleDied);
	}
}

void UScWCharacterMesh_ThirdPerson::InitFromASC(UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) // IScWASC_InitInterface
{
	ensureReturn(InInitASC);
	//ensureReturn(InOwnerActor);
	//ensureReturn(InAvatarActor);

	InInitASC->RegisterGameplayTagEvent(FScWCoreTags::Camera_Type_FirstPerson, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnOwnerCameraTypeFirstPersonTagChanged);
	OnOwnerCameraTypeFirstPersonTagChanged(FScWCoreTags::Camera_Type_FirstPerson, InInitASC->GetGameplayTagCount(FScWCoreTags::Camera_Type_FirstPerson));

	MassChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetMassAttribute()).AddUObject(this, &ThisClass::OnMassAttributeChanged);
}
//~ End Initialize

//~ Begin Camera
void UScWCharacterMesh_ThirdPerson::OnOwnerCameraTypeFirstPersonTagChanged(const FGameplayTag InCallbackTag, int32 InNewCount)
{
	if (InNewCount > 0)
	{
		SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::WorldSpaceRepresentation);
	}
	else
	{
		SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::None);
	}
}
//~ End Camera

//~ Begin Animations
UScWAnimInstance_ThirdPerson* UScWCharacterMesh_ThirdPerson::GetScWThirdPersonAnimInstance() const
{
	return Cast<UScWAnimInstance_ThirdPerson>(GetAnimInstance());
}

void UScWCharacterMesh_ThirdPerson::SetAnimInstanceClass(class UClass* InNewClass) // USkeletalMeshComponent
{
	Super::SetAnimInstanceClass(InNewClass);

	if (UScWAnimInstance_ThirdPerson* AnimInstance = GetScWThirdPersonAnimInstance())
	{
		AnimInstance->SetDefaultStaticAnimationData(DefaultStaticAnimationData);
	}
}
//~ End Animations

//~ Begin Attributes
void UScWCharacterMesh_ThirdPerson::OnMassAttributeChanged(const FOnAttributeChangeData& InData)
{
	SetAllMassScale(1.0f);
	SetAllMassScale(InData.NewValue / GetMass());
}
//~ End Attributes

//~ Begin Damage
void UScWCharacterMesh_ThirdPerson::BP_ActivateRagdoll_Implementation()
{
	SetSimulatePhysics(true);
	SetCollisionProfileName(RagdollCollisionProfileName);
}

void UScWCharacterMesh_ThirdPerson::HandleDamageApplied(float InDamage, const FReceivedDamageData& InData)
{
	if (IsSimulatingPhysics())
	{
		ensureReturn(InData.DamageType);
		InData.DamageType->ApplyImpactImpulseToPhysicsBody(this, InData.HitResult);
	}
}

void UScWCharacterMesh_ThirdPerson::HandleDied()
{
	BP_PostDeathBehavior();
}

void UScWCharacterMesh_ThirdPerson::BP_PostDeathBehavior_Implementation()
{
	BP_ActivateRagdoll();
}
//~ End Damage
