// Scientific Ways

#include "Character/ScWCharacter.h"

//#include "AI/ScWAIController.h"

#include "Tags/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "Character/ScWPawnExtensionComponent.h"

#include "Game/ScWGameState.h"

#include "Character/ScWCharacterCapsule.h"
#include "Character/ScWCharacterMovement.h"
#include "Character/ScWPawnExtensionComponent.h"
#include "Character/ScWCharacterMesh_FirstPerson.h"
#include "Character/ScWCharacterMesh_ThirdPerson.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AScWCharacter::AScWCharacter(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer
		.SetDefaultSubobjectClass<UScWCharacterMesh_ThirdPerson>(ACharacter::MeshComponentName)
		.SetDefaultSubobjectClass<UScWCharacterMovement>(ACharacter::CharacterMovementComponentName)
		.SetDefaultSubobjectClass<UScWCharacterCapsule>(ACharacter::CapsuleComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	//AIControllerClass = AScWAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PawnExtComponent = CreateDefaultSubobject<UScWPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemInitialized));
	PawnExtComponent->OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemUninitialized));

	ScWThirdPersonCharacterMesh = Cast<UScWCharacterMesh_ThirdPerson>(GetMesh());
	ScWCharacterMovement = Cast<UScWCharacterMovement>(GetCharacterMovement());
	ScWCharacterCapsule = Cast<UScWCharacterCapsule>(GetCapsuleComponent());
}

//~ Begin Initialize
void AScWCharacter::PostInitializeComponents() // AActor
{
	Super::PostInitializeComponents();

	ForEachComponent(false, [this](UActorComponent* InComponent)
	{
		if (UCameraComponent* SampleCameraComponent = Cast<UCameraComponent>(InComponent))
		{
			ensureReturn(CachedCameraComponent == nullptr);
			CachedCameraComponent = SampleCameraComponent;

			if (USpringArmComponent* SampleSpringArmComponent = Cast<USpringArmComponent>(CachedCameraComponent->GetAttachParent()))
			{
				ensureReturn(CachedCameraSpringArmComponent == nullptr);
				CachedCameraSpringArmComponent = SampleSpringArmComponent;
			}
		}
		else if (UScWCharacterMesh_FirstPerson* SampleFirstPersonMeshComponent = Cast<UScWCharacterMesh_FirstPerson>(InComponent))
		{
			ensureReturn(ScWFirstPersonCharacterMesh == nullptr);
			ScWFirstPersonCharacterMesh = SampleFirstPersonMeshComponent;
		}
	});
}

void AScWCharacter::OnConstruction(const FTransform& InTransform) // AActor
{
	Super::OnConstruction(InTransform);

	
}

void AScWCharacter::BeginPlay() // AActor
{
	Super::BeginPlay();

	
}

void AScWCharacter::EndPlay(const EEndPlayReason::Type InReason) // AActor
{
	// Uninitialize the ASC if we're still the avatar actor (otherwise another pawn already did it when they became the avatar actor)
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		if (ASC->GetAvatarActor() == this)
		{
			PawnExtComponent->UninitializeAbilitySystem();
		}
	}
	Super::EndPlay(InReason);
}
//~ End Initialize

//~ Begin Replication
void AScWCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME_CONDITION(ThisClass, ReplicatedAcceleration, COND_SimulatedOnly);
	//DOREPLIFETIME(ThisClass, CurrentTeamID)
}

void AScWCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);

	/*if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		// Compress Acceleration: XY components as direction + magnitude, Z component as direct value
		const double MaxAccel = MovementComponent->MaxAcceleration;
		const FVector CurrentAccel = MovementComponent->GetCurrentAcceleration();
		double AccelXYRadians, AccelXYMagnitude;
		FMath::CartesianToPolar(CurrentAccel.X, CurrentAccel.Y, AccelXYMagnitude, AccelXYRadians);

		ReplicatedAcceleration.AccelXYRadians = FMath::FloorToInt((AccelXYRadians / TWO_PI) * 255.0);     // [0, 2PI] -> [0, 255]
		ReplicatedAcceleration.AccelXYMagnitude = FMath::FloorToInt((AccelXYMagnitude / MaxAccel) * 255.0);	// [0, MaxAccel] -> [0, 255]
		ReplicatedAcceleration.AccelZ = FMath::FloorToInt((CurrentAccel.Z / MaxAccel) * 127.0);   // [-MaxAccel, MaxAccel] -> [-127, 127]
	}*/
}

void AScWCharacter::OnRep_Controller() // APawn
{
	Super::OnRep_Controller();
	PawnExtComponent->HandleControllerChanged();
}

void AScWCharacter::OnRep_PlayerState() // APawn
{
	Super::OnRep_PlayerState();
	PawnExtComponent->HandlePlayerStateReplicated();
}
//~ End Replication

//~ Begin Ability System
UAbilitySystemComponent* AScWCharacter::GetAbilitySystemComponent() const // IAbilitySystemInterface
{
	ensureReturn(PawnExtComponent, nullptr);
	return PawnExtComponent->GetScWAbilitySystemComponent();
}

void AScWCharacter::OnAbilitySystemInitialized()
{
	InitializeGameplayTags();
}

void AScWCharacter::OnAbilitySystemUninitialized()
{
	
}
//~ End Ability System

//~ Begin Gameplay Tags
void AScWCharacter::GetOwnedGameplayTags(FGameplayTagContainer& OutTagContainer) const // IGameplayTagAssetInterface
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	ensureReturn(ASC);
	ASC->GetOwnedGameplayTags(OutTagContainer);
}

bool AScWCharacter::HasMatchingGameplayTag(FGameplayTag InTagToCheck) const // IGameplayTagAssetInterface
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	ensureReturn(ASC, false);
	return ASC->HasMatchingGameplayTag(InTagToCheck);
}

bool AScWCharacter::HasAllMatchingGameplayTags(const FGameplayTagContainer& InTagContainer) const // IGameplayTagAssetInterface
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	ensureReturn(ASC, false);
	return ASC->HasAllMatchingGameplayTags(InTagContainer);
}

bool AScWCharacter::HasAnyMatchingGameplayTags(const FGameplayTagContainer& InTagContainer) const // IGameplayTagAssetInterface
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	ensureReturn(ASC, false);
	return ASC->HasAnyMatchingGameplayTags(InTagContainer);
}

void AScWCharacter::InitializeGameplayTags()
{
	
}
//~ End Gameplay Tags

//~ Begin Gameplay Cues
void AScWCharacter::HandleGameplayCue(UObject* InSelf, FGameplayTag InGameplayCueTag, EGameplayCueEvent::Type InEventType, const FGameplayCueParameters& InParameters) // IGameplayCueInterface
{

}
//~ End Gameplay Cues

//~ Begin Components
UActorComponent* AScWCharacter::FindComponentByClass(const TSubclassOf<UActorComponent> InComponentClass) const
{
	ensureReturn(InComponentClass, nullptr);

	if (ScWThirdPersonCharacterMesh && ScWThirdPersonCharacterMesh->IsA(InComponentClass))
	{
		return ScWThirdPersonCharacterMesh;
	}
	else if (ScWFirstPersonCharacterMesh && ScWFirstPersonCharacterMesh->IsA(InComponentClass))
	{
		return ScWFirstPersonCharacterMesh;
	}
	else if (ScWCharacterMovement && ScWCharacterMovement->IsA(InComponentClass))
	{
		return ScWCharacterMovement;
	}
	else if (ScWCharacterCapsule && ScWCharacterCapsule->IsA(InComponentClass))
	{
		return ScWCharacterCapsule;
	}
	return Super::FindComponentByClass(InComponentClass);
}

UScWAnimInstance_FirstPerson* AScWCharacter::GetScWFirstPersonAnimInstance() const
{
	ensureReturn(ScWFirstPersonCharacterMesh, nullptr);
	return ScWFirstPersonCharacterMesh->GetScWFirstPersonAnimInstance();
}

UScWAnimInstance_ThirdPerson* AScWCharacter::GetScWThirdPersonAnimInstance() const
{
	ensureReturn(ScWThirdPersonCharacterMesh, nullptr);
	return ScWThirdPersonCharacterMesh->GetScWThirdPersonAnimInstance();
}
//~ End Components

//~ Begin Input
void AScWCharacter::SetupPlayerInputComponent(UInputComponent* InInputComponent) // APawn
{
	Super::SetupPlayerInputComponent(InInputComponent);
	PawnExtComponent->SetupPlayerInputComponent();
}
//~ End Input

//~ Begin Controller
FVector AScWCharacter::GetPawnViewLocation() const // APawn
{
	return Super::GetPawnViewLocation();
}

void AScWCharacter::SpawnDefaultController() // APawn
{
	Super::SpawnDefaultController();


}

void AScWCharacter::PossessedBy(AController* NewController) // APawn
{
	//const FGenericTeamId OldTeamID = CurrentTeamID;
	const FGameplayTag OldTeamTag = GetTeamTag();

	Super::PossessedBy(NewController);

	PawnExtComponent->HandleControllerChanged();

	// Grab the current team ID and listen for future changes
	if (IScWTeamAgentInterface* ControllerAsTeamProvider = Cast<IScWTeamAgentInterface>(NewController))
	{
		//CurrentTeamID = ControllerAsTeamProvider->GetGenericTeamId();
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().AddDynamic(this, &ThisClass::OnControllerChangedTeam);
	}
	//ConditionalBroadcastTeamChanged(this, OldTeamID, CurrentTeamID);
	ConditionalBroadcastTeamChanged(this, OldTeamTag, GetTeamTag());
}

void AScWCharacter::UnPossessed() // APawn
{
	AController* const OldController = GetController();

	// Stop listening for changes from the old controller
	//const FGenericTeamId OldTeamID = CurrentTeamID;
	const FGameplayTag OldTeamTag = GetTeamTag();
	if (IScWTeamAgentInterface* ControllerAsTeamProvider = Cast<IScWTeamAgentInterface>(OldController))
	{
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().RemoveAll(this);
	}
	Super::UnPossessed();

	PawnExtComponent->HandleControllerChanged();

	// Determine what the new team ID should be afterwards
	//CurrentTeamID = DetermineNewTeamAfterPossessionEnds(OldTeamID);
	//ConditionalBroadcastTeamChanged(this, OldTeamID, CurrentTeamID);
	ConditionalBroadcastTeamChanged(this, OldTeamTag, GetTeamTag());
}

void AScWCharacter::NotifyControllerChanged() // APawn
{
	Super::NotifyControllerChanged();

	
}
//~ End Controller

//~ Begin View
void AScWCharacter::CalcCamera(float InDeltaSeconds, FMinimalViewInfo& InOutResult) // AActor
{
	if (CachedCameraComponent && CachedCameraComponent->IsActive())
	{
		CachedCameraComponent->GetCameraView(InDeltaSeconds, InOutResult);
	}
	else
	{
		Super::CalcCamera(InDeltaSeconds, InOutResult);
	}
}

bool AScWCharacter::HasActiveCameraComponent(bool bInForceFindCamera) const // AActor
{
	if (CachedCameraComponent && CachedCameraComponent->IsActive())
	{
		return true;
	}
	return Super::HasActiveCameraComponent(bInForceFindCamera);
}

bool AScWCharacter::HasActivePawnControlCameraComponent() const // AActor
{
	if (CachedCameraComponent&& CachedCameraComponent->IsActive() && (CachedCameraComponent->bUsePawnControlRotation || (CachedCameraSpringArmComponent && CachedCameraSpringArmComponent->bUsePawnControlRotation)))
	{
		return true;
	}
	return Super::HasActivePawnControlCameraComponent();
}
//~ End View

//~ Begin Team
FGenericTeamId AScWCharacter::GetGenericTeamId() const // IGenericTeamAgentInterface
{
	//return CurrentTeamID;
	IScWTeamAgentInterface* ControllerTeamInterface = Cast<IScWTeamAgentInterface>(GetController());
	ensureReturn(ControllerTeamInterface, FGenericTeamId::NoTeam);
	return ControllerTeamInterface->GetGenericTeamId();
}

void AScWCharacter::SetGenericTeamId(const FGenericTeamId& InTeamID) // IGenericTeamAgentInterface
{
	IScWTeamAgentInterface* ControllerTeamInterface = Cast<IScWTeamAgentInterface>(GetController());
	ensureReturn(ControllerTeamInterface);
	ControllerTeamInterface->SetGenericTeamId(InTeamID);
	/*if (GetController() == nullptr)
	{
		if (HasAuthority())
		{
			const FGenericTeamId OldTeamID = CurrentTeamID;
			CurrentTeamID = InTeamID;
			ConditionalBroadcastTeamChanged(this, OldTeamID, CurrentTeamID);
		}
		else
		{
			UE_LOG(LogScWGameCore, Error, TEXT("You can't set the team ID on a character (%s) except on the authority"), *GetPathNameSafe(this));
		}
	}
	else
	{
		UE_LOG(LogScWGameCore, Error, TEXT("You can't set the team ID on a possessed character (%s); it's driven by the associated controller"), *GetPathNameSafe(this));
	}*/
}

const FGameplayTag& AScWCharacter::GetTeamTag() const // IScWTeamAgentInterface
{
	if (IScWTeamAgentInterface* ControllerTeamInterface = Cast<IScWTeamAgentInterface>(GetController()))
	{
		//ensureReturn(ControllerTeamInterface, IScWTeamAgentInterface::TeamNoneTag);
		return ControllerTeamInterface->GetTeamTag();
	}
	return IScWTeamAgentInterface::TeamNoneTag;
}

void AScWCharacter::SetTeamTag(const FGameplayTag& InTeamTag) // IScWTeamAgentInterface
{
	IScWTeamAgentInterface* ControllerTeamInterface = Cast<IScWTeamAgentInterface>(GetController());
	ensureReturn(ControllerTeamInterface);
	ControllerTeamInterface->SetTeamTag(InTeamTag);
}

FOnScWTeamIndexChangedDelegate* AScWCharacter::GetOnTeamIndexChangedDelegate() // IScWTeamAgentInterface
{
	return &OnTeamChangedDelegate;
}

void AScWCharacter::OnControllerChangedTeam(UObject* TeamAgent, const FGameplayTag& InPrevTeamTag, const FGameplayTag& InNewTeamTag)
{
	//const FGenericTeamId MyOldTeamID = CurrentTeamID;
	//CurrentTeamID = IntegerToGenericTeamId(NewTeam);
	ConditionalBroadcastTeamChanged(this, InPrevTeamTag, InNewTeamTag);
}

/*void AScWCharacter::OnRep_CurrentTeamID(FGenericTeamId OldTeamID)
{
	ConditionalBroadcastTeamChanged(this, OldTeamID, CurrentTeamID);
}*/
//~ End Team
