// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Animation/ScWTypes_Animation.h"
#include "Character/ScWCharacterMesh_Base.h"

#include "ScWCharacterMesh_ThirdPerson.generated.h"

#define MODULE_API SCWGAMECORE_API

class UScWAbilitySystemComponent;
class UScWAnimInstance_ThirdPerson;

/**
 *
 */
UCLASS(ClassGroup = ("Character"), meta = (DisplayName = "[ScW] ThirdPerson Character Mesh (Component)", BlueprintSpawnableComponent))
class UScWCharacterMesh_ThirdPerson : public UScWCharacterMesh_Base
{
	GENERATED_BODY()
	
public:	
	
	UScWCharacterMesh_ThirdPerson();
	
//~ Begin Initialize
protected:
	virtual void BeginPlay() override; // UActorComponent
public:
	virtual void InitFromASC(class UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) override; // IScWASC_InitInterface
//~ End Initialize
	
//~ Begin Animations
public:

	UFUNCTION(Category = "Animations", BlueprintCallable, meta = (KeyWords = "GetAnimInstance, GetThirdPerson", DisplayName = "Get ScW Anim Instance (ThirdPerson)"))
	MODULE_API UScWAnimInstance_ThirdPerson* GetScWThirdPersonAnimInstance() const;
	
protected:
	virtual void SetAnimInstanceClass(UClass* InNewClass) override; // USkeletalMeshComponent

	UPROPERTY(Category = "Animations", EditAnywhere, BlueprintReadOnly)
	FScWThirdPersonStaticAnimationData DefaultStaticAnimationData;
//~ End Animations

//~ Begin Camera
protected:
	virtual void OnOwnerCameraTypeFirstPersonTagChanged(const FGameplayTag InCallbackTag, int32 InNewCount);
//~ End Camera

//~ Begin Attributes
protected:
	void OnMassAttributeChanged(const FOnAttributeChangeData& InData);
	FDelegateHandle MassChangedDelegateHandle;
//~ End Attributes

//~ Begin Damage
public:

	UFUNCTION(Category = "Damage", BlueprintNativeEvent, BlueprintCallable, BlueprintCosmetic, meta = (DisplayName = "Activate Ragdoll"))
	MODULE_API void BP_ActivateRagdoll();

	UPROPERTY(Category = "Damage", EditAnywhere, BlueprintReadWrite)
	FName RagdollCollisionProfileName;

protected:

	UFUNCTION()
	void HandleDamageApplied(float InDamage, const struct FReceivedDamageData& InData);

	UFUNCTION()
	void HandleDied();

	UFUNCTION(Category = "Damage", BlueprintNativeEvent, meta = (DisplayName = "Post Death Behavior"))
	void BP_PostDeathBehavior();
//~ End Damage
};

#undef MODULE_API
