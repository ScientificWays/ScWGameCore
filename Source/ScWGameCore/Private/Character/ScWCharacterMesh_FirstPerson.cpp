// Scientific Ways

#include "Character/ScWCharacterMesh_FirstPerson.h"

#include "Animation/ScWAnimInstance_FirstPerson.h"
#include "Animation/ScWAnimationsFunctionLibrary.h"

#include "AbilitySystem/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "GameFramework/SpringArmComponent.h"

/*static TAutoConsoleVariable<float> CVarFOVFP(
	TEXT("FOVFP"),
	90.0f,
	TEXT("Modify the FOV of first person meshes."),
	ECVF_SetByGameSetting
);*/

UScWCharacterMesh_FirstPerson::UScWCharacterMesh_FirstPerson()
{
	FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

	//OverrideFOV = 90.0f;

	DefaultSwaySpeed = 50.0f;
	DefaultSwayRotationSpeed = 30.0f;
	DefaultSwayMaxDistance = 1.0f;

	AimingSwaySpeed = 70.0f;
	AimingSwayRotationSpeed = 50.0f;
	AimingSwayMaxDistance = 0.2f;
}

//~ Begin Initialize
void UScWCharacterMesh_FirstPerson::BeginPlay() // UActorComponent
{
	Super::BeginPlay();

	UpdateSwaySpringArmComponent();
}

void UScWCharacterMesh_FirstPerson::UpdateSwaySpringArmComponent()
{
	if (SwaySpringArmComponent == nullptr)
	{
		return;
	}
	if (UScWAbilitySystemComponent* InitASC = GetInitASC())
	{
		SwaySpringArmComponent->TargetArmLength = 0.0f;
		SwaySpringArmComponent->bDoCollisionTest = false;
		SwaySpringArmComponent->bEnableCameraLag = true;
		SwaySpringArmComponent->bEnableCameraRotationLag = true;
		SwaySpringArmComponent->bUseCameraLagSubstepping = false;

		if (InitASC->HasMatchingGameplayTag(FScWCoreTags::State_Aiming))
		{
			SwaySpringArmComponent->CameraLagSpeed = AimingSwaySpeed;
			SwaySpringArmComponent->CameraRotationLagSpeed = AimingSwayRotationSpeed;
			SwaySpringArmComponent->CameraLagMaxDistance = AimingSwayMaxDistance;
		}
		else
		{
			SwaySpringArmComponent->CameraLagSpeed = DefaultSwaySpeed;
			SwaySpringArmComponent->CameraRotationLagSpeed = DefaultSwayRotationSpeed;
			SwaySpringArmComponent->CameraLagMaxDistance = DefaultSwayMaxDistance;
		}
	}
}

void UScWCharacterMesh_FirstPerson::InitFromASC(UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) // IScWASC_InitInterface
{
	ensureReturn(InInitASC);
	//ensureReturn(InOwnerActor);
	//ensureReturn(InAvatarActor);
	Super::InitFromASC(InInitASC, InOwnerActor, InAvatarActor);

	InInitASC->RegisterGameplayTagEvent(FScWCoreTags::Camera_Type_FirstPerson, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnOwnerCameraTypeFirstPersonTagChanged);
	OnOwnerCameraTypeFirstPersonTagChanged(FScWCoreTags::Camera_Type_FirstPerson, InInitASC->GetGameplayTagCount(FScWCoreTags::Camera_Type_FirstPerson));

	InInitASC->RegisterGameplayTagEvent(FScWCoreTags::State_Aiming, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnAimingTagChanged);
	UpdateSwaySpringArmComponent();

	if (InInitASC->AbilityActorInfo.IsValid() && InInitASC->AbilityActorInfo->PlayerController.IsValid())
	{
		PlayerCameraManager = InInitASC->AbilityActorInfo->PlayerController->PlayerCameraManager;
	}
}
//~ End Initialize

//~ Begin Animations
UScWAnimInstance_FirstPerson* UScWCharacterMesh_FirstPerson::GetScWFirstPersonAnimInstance() const
{
	return Cast<UScWAnimInstance_FirstPerson>(GetAnimInstance());
}

void UScWCharacterMesh_FirstPerson::SetAnimInstanceClass(class UClass* InNewClass) // USkeletalMeshComponent
{
	Super::SetAnimInstanceClass(InNewClass);

	if (UScWAnimInstance_FirstPerson* AnimInstance = GetScWFirstPersonAnimInstance())
	{
		AnimInstance->SetDefaultStaticAnimationData(DefaultStaticAnimationData);
	}
}
//~ End Animations

//~ Begin Camera
void UScWCharacterMesh_FirstPerson::OnOwnerCameraTypeFirstPersonTagChanged(const FGameplayTag InCallbackTag, int32 InNewCount)
{
	if (InNewCount > 0)
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}

/*FMatrix UScWCharacterMesh_FirstPerson::GetRenderMatrix() const // UPrimitiveComponent
{
	// Source: https://sahildhanju.com/posts/render-first-person-fov/
	if (PlayerCameraManager == nullptr)
	{
		return Super::GetRenderMatrix();
	}
	const float WorldFOV = PlayerCameraManager->GetFOVAngle();
	const float FirstPersonFOV = CVarFOVFP.GetValueOnGameThread() * (WorldFOV / PlayerCameraManager->DefaultFOV);

	FVector ViewOrigin;
	FRotator ViewRotation;

	PlayerCameraManager->GetCameraViewPoint(ViewOrigin, ViewRotation);

	const float WorldHalfFOVRadians = FMath::DegreesToRadians(FMath::Max(0.001f, WorldFOV)) * 0.5f;
	const float OverrideHalfFOVRadians = FMath::DegreesToRadians(FMath::Max(0.001f, FirstPersonFOV)) * 0.5f;
	const float FOVRatio = WorldHalfFOVRadians / OverrideHalfFOVRadians;

	const FMatrix PerspectiveAdjustmentMatrix = FMatrix(
		FPlane(FOVRatio, 0, 0, 0),
		FPlane(0, FOVRatio, 0, 0),
		FPlane(0, 0, 1, 0),
		FPlane(0, 0, 0, 1));

	FMatrix ViewRotationMatrix = FInverseRotationMatrix(ViewRotation) * FMatrix(
		FPlane(0, 0, 1, 0),
		FPlane(1, 0, 0, 0),
		FPlane(0, 1, 0, 0),
		FPlane(0, 0, 0, 1));

	if (!ViewRotationMatrix.GetOrigin().IsNearlyZero(0.0f))
	{
		ViewOrigin += ViewRotationMatrix.InverseTransformPosition(FVector::ZeroVector);
		ViewRotationMatrix = ViewRotationMatrix.RemoveTranslation();
	}
	const FMatrix ViewMatrix = FTranslationMatrix(-ViewOrigin) * ViewRotationMatrix;
	const FMatrix InverseViewMatrix = FTranslationMatrix(-ViewMatrix.GetOrigin()) * ViewMatrix.RemoveTranslation().GetTransposed();
	const FMatrix AdjustedRenderMatrix = GetComponentToWorld().ToMatrixWithScale() * ViewMatrix * PerspectiveAdjustmentMatrix * InverseViewMatrix;

	return AdjustedRenderMatrix;
}*/
//~ End Camera

//~ Begin Sway
void UScWCharacterMesh_FirstPerson::OnAimingTagChanged(const FGameplayTag InCallbackTag, int32 InNewCount)
{
	UpdateSwaySpringArmComponent();
}
//~ End Sway
