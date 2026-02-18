// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"

#include "ScWPawnExtensionComponent.generated.h"

#define MODULE_API SCWGAMECORE_API

class UGameFrameworkComponentManager;
class UScWAbilitySystemComponent;
class UScWPawnData;
struct FActorInitStateChangedParams;
struct FFrame;
struct FGameplayTag;

/**
 *	Component that adds functionality to all Pawn classes so it can be used for characters/vehicles/etc.
 *	This coordinates the initialization of other components.
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Pawn Extension Component"))
class UScWPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:

	MODULE_API UScWPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

	/** The name of this overall feature, this one depends on the other named component features */
	static MODULE_API const FName NAME_ActorFeatureName;

	//~ Begin IGameFrameworkInitStateInterface interface
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }
	MODULE_API virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	MODULE_API virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	MODULE_API virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	MODULE_API virtual void CheckDefaultInitialization() override;
	//~ End IGameFrameworkInitStateInterface interface

	/** Returns the pawn extension component if one exists on the specified actor. */
	UFUNCTION(Category = "Statics", BlueprintPure)
	static UScWPawnExtensionComponent* GetPawnExtensionComponent(const AActor* InActor)
	{
		ensureReturn(InActor, nullptr);
		return InActor->FindComponentByClass<ThisClass>();
	}

	/** Gets the pawn data, which is used to specify pawn properties in data */
	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

	/** Sets the current pawn data */
	MODULE_API void SetPawnData(const UScWPawnData* InPawnData);

	/** Gets the current ability system component, which may be owned by a different actor */
	UFUNCTION(BlueprintPure, Category = "ScW | Pawn")
	UScWAbilitySystemComponent* GetScWAbilitySystemComponent() const { return AbilitySystemComponent; }

	/** Should be called by the owning pawn to become the avatar of the ability system. */
	MODULE_API void InitializeAbilitySystem(UScWAbilitySystemComponent* InASC, AActor* InOwnerActor);

	/** Should be called by the owning pawn to remove itself as the avatar of the ability system. */
	MODULE_API void UninitializeAbilitySystem();

	/** Should be called by the owning pawn when the pawn's controller changes. */
	MODULE_API void HandleControllerChanged();

	/** Should be called by the owning pawn when the player state has been replicated. */
	MODULE_API void HandlePlayerStateReplicated();

	/** Should be called by the owning pawn when the input component is setup. */
	MODULE_API void SetupPlayerInputComponent();

	/** Register with the OnAbilitySystemInitialized delegate and broadcast if our pawn has been registered with the ability system component */
	MODULE_API void OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate);

	/** Register with the OnAbilitySystemUninitialized delegate fired when our pawn is removed as the ability system's avatar actor */
	MODULE_API void OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate Delegate);

	MODULE_API FSimpleMulticastDelegate& GetOnAbilitySystemInitialized() { return OnAbilitySystemInitialized; }

protected:

	MODULE_API virtual void OnRegister() override;
	MODULE_API virtual void BeginPlay() override;
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	MODULE_API void OnRep_PawnData();

	/** Delegate fired when our pawn becomes the ability system's avatar actor */
	FSimpleMulticastDelegate OnAbilitySystemInitialized;

	/** Delegate fired when our pawn is removed as the ability system's avatar actor */
	FSimpleMulticastDelegate OnAbilitySystemUninitialized;

	/** Pawn data used to create the pawn. Specified from a spawn function or on a placed instance. */
	UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_PawnData, Category = "ScW | Pawn")
	TObjectPtr<const UScWPawnData> PawnData;

	/** Pointer to the ability system component that is cached for convenience. */
	UPROPERTY(Transient)
	TObjectPtr<UScWAbilitySystemComponent> AbilitySystemComponent;
};

#undef MODULE_API
