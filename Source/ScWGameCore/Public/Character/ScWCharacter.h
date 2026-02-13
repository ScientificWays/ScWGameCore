// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ModularCharacter.h"
#include "Team/ScWTeamAgentInterface.h"

#include "Utils/ScWTypes_CommonDelegates.h"

#include "ScWCharacter.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *
 */
UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (DisplayName = "[ScW] Character"))
class AScWCharacter : public AModularCharacter, public IScWTeamAgentInterface, public IAbilitySystemInterface, public IGameplayTagAssetInterface, public IGameplayCueInterface
{
	GENERATED_BODY()

public:

	AScWCharacter(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

//~ Begin Initialize
protected:
	virtual void PostInitializeComponents() override; // AActor
	virtual void OnConstruction(const FTransform& InTransform) override; // AActor
	virtual void BeginPlay() override; // AActor
	virtual void EndPlay(const EEndPlayReason::Type InReason) override; // AActor
//~ End Initialize
	
//~ Begin Replication
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // AActor
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override; // AActor
	virtual void OnRep_Controller() override; // APawn
	virtual void OnRep_PlayerState() override; // APawn
//~ End Replication
	
//~ Begin Ability System
public:
	MODULE_API virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // IAbilitySystemInterface
protected:
	virtual void OnAbilitySystemInitialized();
	virtual void OnAbilitySystemUninitialized();
//~ End Ability System

//~ Begin Gameplay Tags
public:
	MODULE_API virtual void GetOwnedGameplayTags(FGameplayTagContainer& OutTagContainer) const override; // IGameplayTagAssetInterface
	MODULE_API virtual bool HasMatchingGameplayTag(FGameplayTag InTagToCheck) const override; // IGameplayTagAssetInterface
	MODULE_API virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& InTagContainer) const override; // IGameplayTagAssetInterface
	MODULE_API virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& InTagContainer) const override; // IGameplayTagAssetInterface
protected:
	virtual void InitializeGameplayTags();
//~ End Gameplay Tags

//~ Begin Gameplay Cues
protected:
	virtual void HandleGameplayCue(UObject* InSelf, FGameplayTag InGameplayCueTag, EGameplayCueEvent::Type InEventType, const FGameplayCueParameters& InParameters) override; // IGameplayCueInterface
//~ End Gameplay Cues

//~ Begin Components
public:
	virtual UActorComponent* FindComponentByClass(const TSubclassOf<UActorComponent> InComponentClass) const override; // AActor

	UFUNCTION(Category = "Components", BlueprintCallable, meta = (KeyWords = "GetCharacterMesh, GetMesh, GetCharacterMesh, GetFirstPerson", DisplayName = "Get ScW Character Mesh (FirstPerson)"))
	MODULE_API class UScWCharacterMesh_FirstPerson* GetScWFirstPersonCharacterMesh() const { return ScWFirstPersonCharacterMesh; }

	UFUNCTION(Category = "Components", BlueprintCallable, meta = (KeyWords = "GetAnimInstance, GetFirstPerson", DisplayName = "Get ScW Anim Instance (FirstPerson)"))
	MODULE_API class UScWAnimInstance_FirstPerson* GetScWFirstPersonAnimInstance() const;

	UFUNCTION(Category = "Components", BlueprintCallable, meta = (KeyWords = "GetCharacterMesh, GetMesh, GetCharacterMesh, GetThirdPerson", DisplayName = "Get ScW Character Mesh (ThirdPerson)"))
	MODULE_API class UScWCharacterMesh_ThirdPerson* GetScWThirdPersonCharacterMesh() const { return ScWThirdPersonCharacterMesh; }

	UFUNCTION(Category = "Components", BlueprintCallable, meta = (KeyWords = "GetAnimInstance, GetThirdPerson", DisplayName = "Get ScW Anim Instance (FirstPerson)"))
	MODULE_API class UScWAnimInstance_ThirdPerson* GetScWThirdPersonAnimInstance() const;

	UFUNCTION(Category = "Components", BlueprintCallable, meta = (KeyWords = "GetCharacterMovementComponent, GetCMC", DisplayName = "Get ScW Character Movement"))
	MODULE_API class UScWCharacterMovement* GetScWCharacterMovement() const { return ScWCharacterMovement; }

	UFUNCTION(Category = "Components", BlueprintCallable, meta = (KeyWords = "GetCharacterCapsuleComponent, GetCapsule", DisplayName = "Get ScW Character Capsule"))
	MODULE_API class UScWCharacterCapsule* GetScWCharacterCapsule() const { return ScWCharacterCapsule; }

protected:

	UPROPERTY(Category = "Components", BlueprintReadOnly)
	TObjectPtr<class UScWCharacterMesh_FirstPerson> ScWFirstPersonCharacterMesh;

	UPROPERTY(Category = "Components", BlueprintReadOnly)
	TObjectPtr<class UScWCharacterMesh_ThirdPerson> ScWThirdPersonCharacterMesh;

	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class UScWCharacterMovement> ScWCharacterMovement;

	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class UScWCharacterCapsule> ScWCharacterCapsule;

	UPROPERTY(Category = "Components", BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class UScWPawnExtensionComponent> PawnExtComponent;
//~ End Components
	
//~ Begin Input
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InInputComponent) override; // APawn
//~ End Input
	
//~ Begin Controller
public:
	virtual FVector GetPawnViewLocation() const override; // APawn
protected:
	virtual void SpawnDefaultController() override; // APawn
	virtual void PossessedBy(AController* InController) override; // APawn
	virtual void UnPossessed() override; // APawn
	virtual void NotifyControllerChanged() override; // APawn
//~ End Controller

//~ Begin View
public:
	virtual void CalcCamera(float InDeltaSeconds, FMinimalViewInfo& InOutResult) override; // AActor
	virtual bool HasActiveCameraComponent(bool bInForceFindCamera = false) const override; // AActor
	virtual bool HasActivePawnControlCameraComponent() const override; // AActor
protected:

	UPROPERTY(Transient)
	TObjectPtr<class UCameraComponent> CachedCameraComponent;

	UPROPERTY(Transient)
	TObjectPtr<class USpringArmComponent> CachedCameraSpringArmComponent;
//~ End View

//~ Begin Team
protected:
	virtual FGenericTeamId GetGenericTeamId() const override; // IGenericTeamAgentInterface
	virtual void SetGenericTeamId(const FGenericTeamId& InNewTeamID) override; // IGenericTeamAgentInterface
	virtual FOnScWTeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() override; // IScWTeamAgentInterface

	UFUNCTION()
	void OnControllerChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam);

	UPROPERTY(ReplicatedUsing = "OnRep_CurrentTeamID")
	FGenericTeamId CurrentTeamID;

	UPROPERTY()
	FOnScWTeamIndexChangedDelegate OnTeamChangedDelegate;

	UFUNCTION()
	MODULE_API virtual void OnRep_CurrentTeamID(FGenericTeamId OldTeamID);

	// Called to determine what happens to the team ID when possession ends
	virtual FGenericTeamId DetermineNewTeamAfterPossessionEnds(FGenericTeamId OldTeamID) const
	{
		// This could be changed to return, e.g., OldTeamID if you want to keep it assigned afterwards, or return an ID for some neutral faction, or etc...
		return FGenericTeamId::NoTeam;
	}
//~ End Team
};

#undef MODULE_API
