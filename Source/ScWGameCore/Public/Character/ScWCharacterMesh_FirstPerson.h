// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Animation/ScWTypes_Animation.h"
#include "Character/ScWCharacterMesh_Base.h"

#include "ScWCharacterMesh_FirstPerson.generated.h"

#define MODULE_API SCWGAMECORE_API

class UScWAbilitySystemComponent;
class UScWAnimInstance_FirstPerson;

/**
 * 
 */
UCLASS(ClassGroup = ("Character"), meta = (DisplayName = "[ScW] FirstPerson Character Mesh (Component)", BlueprintSpawnableComponent))
class UScWCharacterMesh_FirstPerson : public UScWCharacterMesh_Base
{
	GENERATED_BODY()

public:

	UScWCharacterMesh_FirstPerson();

//~ Begin Initialize
protected:
	virtual void BeginPlay() override; // UActorComponent
	virtual void UpdateSwaySpringArmComponent();
public:
	virtual void InitFromASC(UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) override; // IScWASC_InitInterface
//~ End Initialize
	
//~ Begin Animations
public:

	UFUNCTION(Category = "Animations", BlueprintCallable, meta = (KeyWords = "GetAnimInstance, GetFirstPerson", DisplayName = "Get ScW Anim Instance (FirstPerson)"))
	MODULE_API UScWAnimInstance_FirstPerson* GetScWFirstPersonAnimInstance() const;

protected:
	virtual void SetAnimInstanceClass(UClass* InNewClass) override; // USkeletalMeshComponent

	UPROPERTY(Category = "Animations", EditAnywhere, BlueprintReadOnly)
	FScWFirstPersonStaticAnimationData DefaultStaticAnimationData;
//~ End Animations

//~ Begin Camera
public:

	//UPROPERTY(Category = FOV, EditAnywhere, BlueprintReadWrite)
	//float OverrideFOV;

protected:
	virtual void OnOwnerCameraTypeFirstPersonTagChanged(const FGameplayTag InCallbackTag, int32 InNewCount);
	//virtual FMatrix GetRenderMatrix() const override; // UPrimitiveComponent

	UPROPERTY(Transient)
	TObjectPtr<APlayerCameraManager> PlayerCameraManager;
//~ End Camera

//~ Begin Sway
protected:
	///virtual void OnAimingTagChanged(const FGameplayTag InCallbackTag, int32 InNewCount);

	UPROPERTY(Category = "Sway", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USpringArmComponent> SwaySpringArmComponent;

	UPROPERTY(Category = "Sway", EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SwaySpringArmComponent != nullptr", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
	float DefaultSwaySpeed;

	UPROPERTY(Category = "Sway", EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SwaySpringArmComponent != nullptr", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
	float DefaultSwayRotationSpeed;

	UPROPERTY(Category = "Sway", EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SwaySpringArmComponent != nullptr", ClampMin = "0.0", UIMin = "0.0"))
	float DefaultSwayMaxDistance;

	//UPROPERTY(Category = "Sway", EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SwaySpringArmComponent != nullptr", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
	//float AimingSwaySpeed;

	//UPROPERTY(Category = "Sway", EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SwaySpringArmComponent != nullptr", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
	//float AimingSwayRotationSpeed;

	//UPROPERTY(Category = "Sway", EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SwaySpringArmComponent != nullptr", ClampMin = "0.0", UIMin = "0.0"))
	//float AimingSwayMaxDistance;
//~ End Sway
};

#undef MODULE_API
