// Scientific Ways

#pragma once

#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "Features/ScWGFA_AddInputContextMapping.h"
#include "GameplayAbilitySpecHandle.h"
#include "ScWHeroComponent.generated.h"

#define MODULE_API SCWGAMECORE_API

namespace EEndPlayReason { enum Type : int; }
struct FLoadedMappableConfigPair;
struct FMappableConfigPair;

class UGameFrameworkComponentManager;
class UInputComponent;
//class UScWCameraMode;
class UScWInputConfig;
class UObject;
struct FActorInitStateChangedParams;
struct FFrame;
struct FGameplayTag;
struct FInputActionValue;

/**
 * Component that sets up input and camera handling for player controlled pawns (or bots that simulate players).
 * This depends on a PawnExtensionComponent to coordinate initialization.
 */
UCLASS(MinimalAPI, Blueprintable, meta = (BlueprintSpawnableComponent, DisplayName = "[ScW] Hero Component"))
class UScWHeroComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:

	MODULE_API UScWHeroComponent(const FObjectInitializer& ObjectInitializer);

	/** Returns the hero component if one exists on the specified actor. */
	UFUNCTION(BlueprintPure, Category = "ScW | Hero")
	static UScWHeroComponent* FindHeroComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UScWHeroComponent>() : nullptr); }

	/** Overrides the camera from an active gameplay ability */
	//MODULE_API void SetAbilityCameraMode(TSubclassOf<UScWCameraMode> CameraMode, const FGameplayAbilitySpecHandle& OwningSpecHandle);

	/** Clears the camera override if it is set */
	//MODULE_API void ClearAbilityCameraMode(const FGameplayAbilitySpecHandle& OwningSpecHandle);

	/** Adds mode-specific input config */
	MODULE_API void AddAdditionalInputConfig(const UScWInputConfig* InInputConfig);

	/** Removes a mode-specific input config if it has been added */
	MODULE_API void RemoveAdditionalInputConfig(const UScWInputConfig* InInputConfig);

	/** True if this is controlled by a real player and has progressed far enough in initialization where additional input bindings can be added */
	MODULE_API bool IsReadyToBindInputs() const;
	
	/** The name of the extension event sent via UGameFrameworkComponentManager when ability inputs are ready to bind */
	static MODULE_API const FName NAME_BindInputsNow;

	/** The name of this component-implemented feature */
	static MODULE_API const FName NAME_ActorFeatureName;

	//~ Begin IGameFrameworkInitStateInterface interface
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }
	MODULE_API virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	MODULE_API virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	MODULE_API virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	MODULE_API virtual void CheckDefaultInitialization() override;
	//~ End IGameFrameworkInitStateInterface interface

protected:

	MODULE_API virtual void OnRegister() override;
	MODULE_API virtual void BeginPlay() override;
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	MODULE_API virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);

	MODULE_API void Input_AbilityTagPressed(FGameplayTag InputTag);
	MODULE_API void Input_AbilityTagReleased(FGameplayTag InputTag);

	UFUNCTION(Category = "Input", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Get Movement Input World Direction"))
	MODULE_API FVector BP_GetMovementInputWorldDirection(const FVector& InInputValue) const;

	MODULE_API void Input_Movement(const FInputActionValue& InputActionValue);
	MODULE_API void Input_LookMouse(const FInputActionValue& InputActionValue);
	MODULE_API void Input_LookStick(const FInputActionValue& InputActionValue);
	//MODULE_API void Input_Crouch(const FInputActionValue& InputActionValue);
	//MODULE_API void Input_AutoRun(const FInputActionValue& InputActionValue);

	//MODULE_API TSubclassOf<UScWCameraMode> DetermineCameraMode() const;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UScWInputConfig> PrimaryInputConfig;

protected:
	
	UPROPERTY(EditAnywhere)
	TArray<FInputMappingContextAndPriority> DefaultInputMappings;
	
	/** Camera mode set by an ability. */
	//UPROPERTY()
	//TSubclassOf<UScWCameraMode> AbilityCameraMode;

	/** Spec handle for the last ability to set a camera mode. */
	//FGameplayAbilitySpecHandle AbilityCameraModeOwningSpecHandle;

	/** True when player input bindings have been applied, will never be true for non - players */
	bool bReadyToBindInputs;
};

#undef MODULE_API
