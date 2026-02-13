// Scientific Ways

#include "Character/ScWHeroComponent.h"

#include "AbilitySystem/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "Player/ScWPlayerController.h"
#include "Player/ScWPlayerState.h"
#include "Player/ScWLocalPlayer.h"

#include "Character/ScWPawnData.h"
#include "Character/ScWCharacter.h"
#include "Character/ScWPawnExtensionComponent.h"

//#include "Camera/ScWCameraMode.h"
//#include "Camera/ScWCameraComponent.h"

#include "Input/ScWInputConfig.h"
#include "Input/ScWInputComponent.h"

#include "Components/GameFrameworkComponentManager.h"
#include "PlayerMappableInputConfig.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "InputMappingContext.h"
#include "Components/GameFrameworkComponentDelegates.h"
#include "Logging/MessageLog.h"
#include "EnhancedInputSubsystems.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWHeroComponent)

#if WITH_EDITOR
#include "Misc/UObjectToken.h"
#endif	// WITH_EDITOR

namespace ScWHero
{
	static const float LookYawRate = 300.0f;
	static const float LookPitchRate = 165.0f;
};

const FName UScWHeroComponent::NAME_BindInputsNow("BindInputsNow");
const FName UScWHeroComponent::NAME_ActorFeatureName("Hero");

UScWHeroComponent::UScWHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//AbilityCameraMode = nullptr;
	bReadyToBindInputs = false;
}

void UScWHeroComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetPawn<APawn>())
	{
		UE_LOG(LogScWGameCore, Error, TEXT("[UScWHeroComponent::OnRegister] This component has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint."));

#if WITH_EDITOR
		if (GIsEditor)
		{
			static const FText Message = NSLOCTEXT("ScWHeroComponent", "NotOnPawnError", "has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint. This will cause a crash if you PIE!");
			static const FName HeroMessageLogName = TEXT("ScWHeroComponent");
			
			FMessageLog(HeroMessageLogName).Error()
				->AddToken(FUObjectToken::Create(this, FText::FromString(GetNameSafe(this))))
				->AddToken(FTextToken::Create(Message));
				
			FMessageLog(HeroMessageLogName).Open();
		}
#endif
	}
	else
	{
		// Register with the init state system early, this will only work if this is a game world
		RegisterInitStateFeature();
	}
}

bool UScWHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();

	if (!CurrentState.IsValid() && DesiredState == FScWCoreTags::InitState_Spawned)
	{
		// As long as we have a real pawn, let us transition
		if (Pawn)
		{
			return true;
		}
	}
	else if (CurrentState == FScWCoreTags::InitState_Spawned && DesiredState == FScWCoreTags::InitState_DataAvailable)
	{
		// The player state is required.
		if (!GetPlayerState<AScWPlayerState>())
		{
			return false;
		}

		// If we're authority or autonomous, we need to wait for a controller with registered ownership of the player state.
		if (Pawn->GetLocalRole() != ROLE_SimulatedProxy)
		{
			AController* Controller = GetController<AController>();

			const bool bHasControllerPairedWithPS = (Controller != nullptr) && \
				(Controller->PlayerState != nullptr) && \
				(Controller->PlayerState->GetOwner() == Controller);

			if (!bHasControllerPairedWithPS)
			{
				return false;
			}
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const bool bIsBot = Pawn->IsBotControlled();

		if (bIsLocallyControlled && !bIsBot)
		{
			AScWPlayerController* OwnerPC = GetController<AScWPlayerController>();

			// The input component and local player is required when locally controlled.
			if (!Pawn->InputComponent || !OwnerPC || !OwnerPC->GetLocalPlayer())
			{
				return false;
			}
		}

		return true;
	}
	else if (CurrentState == FScWCoreTags::InitState_DataAvailable && DesiredState == FScWCoreTags::InitState_DataInitialized)
	{
		// Wait for player state and extension component
		AScWPlayerState* OwnerPS = GetPlayerState<AScWPlayerState>();

		return OwnerPS && Manager->HasFeatureReachedInitState(Pawn, UScWPawnExtensionComponent::NAME_ActorFeatureName, FScWCoreTags::InitState_DataInitialized);
	}
	else if (CurrentState == FScWCoreTags::InitState_DataInitialized && DesiredState == FScWCoreTags::InitState_GameplayReady)
	{
		// TODO add ability initialization checks?
		return true;
	}

	return false;
}

void UScWHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	if (CurrentState == FScWCoreTags::InitState_DataAvailable && DesiredState == FScWCoreTags::InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		AScWPlayerState* OwnerPS = GetPlayerState<AScWPlayerState>();
		if (!ensure(Pawn && OwnerPS))
		{
			return;
		}

		const UScWPawnData* PawnData = nullptr;

		if (UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtComp->GetPawnData<UScWPawnData>();

			// The player state holds the persistent data for this player (state that persists across deaths and multiple pawns).
			// The ability system component and attribute sets live on the player state.
			PawnExtComp->InitializeAbilitySystem(OwnerPS->GetScWAbilitySystemComponent(), OwnerPS);
		}

		if (AScWPlayerController* OwnerPC = GetController<AScWPlayerController>())
		{
			if (Pawn->InputComponent != nullptr)
			{
				InitializePlayerInput(Pawn->InputComponent);
			}
		}

		// Hook up the delegate for all pawns, in case we spectate later
		/*if (PawnData)
		{
			if (UScWCameraComponent* CameraComponent = UScWCameraComponent::FindCameraComponent(Pawn))
			{
				CameraComponent->DetermineCameraModeDelegate.BindUObject(this, &ThisClass::DetermineCameraMode);
			}
		}*/
	}
}

void UScWHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	if (Params.FeatureName == UScWPawnExtensionComponent::NAME_ActorFeatureName)
	{
		if (Params.FeatureState == FScWCoreTags::InitState_DataInitialized)
		{
			// If the extension component says all all other components are initialized, try to progress to next state
			CheckDefaultInitialization();
		}
	}
}

void UScWHeroComponent::CheckDefaultInitialization()
{
	static const TArray<FGameplayTag> StateChain = { FScWCoreTags::InitState_Spawned, FScWCoreTags::InitState_DataAvailable, FScWCoreTags::InitState_DataInitialized, FScWCoreTags::InitState_GameplayReady };

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	ContinueInitStateChain(StateChain);
}

void UScWHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for when the pawn extension component changes init state
	BindOnActorInitStateChanged(UScWPawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	// Notifies that we are done spawning, then try the rest of initialization
	ensure(TryToChangeInitState(FScWCoreTags::InitState_Spawned));
	CheckDefaultInitialization();
}

void UScWHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void UScWHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const UScWLocalPlayer* LP = Cast<UScWLocalPlayer>(PC->GetLocalPlayer());
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (const UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UScWPawnData* PawnData = PawnExtComp->GetPawnData<UScWPawnData>())
		{
			if (const UScWInputConfig* InputConfig = PawnData->InputConfig)
			{
				for (const FInputMappingContextAndPriority& Mapping : DefaultInputMappings)
				{
					if (UInputMappingContext* IMC = Mapping.InputMapping.LoadSynchronous())
					{
						if (Mapping.bRegisterWithSettings)
						{
							if (UEnhancedInputUserSettings* Settings = Subsystem->GetUserSettings())
							{
								Settings->RegisterInputMappingContext(IMC);
							}
							
							FModifyContextOptions Options = {};
							Options.bIgnoreAllPressedKeysUntilRelease = false;
							// Actually add the config to the local player							
							Subsystem->AddMappingContext(IMC, Mapping.Priority, Options);
						}
					}
				}

				// The ScW Input Component has some additional functions to map Gameplay Tags to an Input Action.
				// If you want this functionality but still want to change your input component class, make it a subclass
				// of the UScWInputComponent or modify this component accordingly.
				UScWInputComponent* ScWIC = Cast<UScWInputComponent>(PlayerInputComponent);
				if (ensureMsgf(ScWIC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UScWInputComponent or a subclass of it.")))
				{
					// Add the key mappings that may have been set by the player
					ScWIC->AddInputMappings(InputConfig, Subsystem);

					// This is where we actually bind and input action to a gameplay tag, which means that Gameplay Ability Blueprints will
					// be triggered directly by these input actions Triggered events. 
					TArray<uint32> BindHandles;
					ScWIC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityTagPressed, &ThisClass::Input_AbilityTagReleased, /*out*/ BindHandles);

					ScWIC->BindNativeAction(InputConfig, FScWCoreTags::Input_Movement, ETriggerEvent::Triggered, this, &ThisClass::Input_Movement, /*bLogIfNotFound=*/ false);
					ScWIC->BindNativeAction(InputConfig, FScWCoreTags::Input_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, /*bLogIfNotFound=*/ false);
					ScWIC->BindNativeAction(InputConfig, FScWCoreTags::Input_Look_Stick, ETriggerEvent::Triggered, this, &ThisClass::Input_LookStick, /*bLogIfNotFound=*/ false);
					//ScWIC->BindNativeAction(InputConfig, FScWCoreTags::Input_Crouch, ETriggerEvent::Triggered, this, &ThisClass::Input_Crouch, /*bLogIfNotFound=*/ false);
					//ScWIC->BindNativeAction(InputConfig, FScWCoreTags::Input_AutoRun, ETriggerEvent::Triggered, this, &ThisClass::Input_AutoRun, /*bLogIfNotFound=*/ false);
				}
			}
		}
	}
	if (ensure(!bReadyToBindInputs))
	{
		bReadyToBindInputs = true;
	}
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APlayerController*>(PC), NAME_BindInputsNow);
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APawn*>(Pawn), NAME_BindInputsNow);
}

void UScWHeroComponent::AddAdditionalInputConfig(const UScWInputConfig* InputConfig)
{
	TArray<uint32> BindHandles;

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}
	
	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	if (const UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		UScWInputComponent* ScWIC = Pawn->FindComponentByClass<UScWInputComponent>();
		if (ensureMsgf(ScWIC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UScWInputComponent or a subclass of it.")))
		{
			ScWIC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityTagPressed, &ThisClass::Input_AbilityTagReleased, /*out*/ BindHandles);
		}
	}
}

void UScWHeroComponent::RemoveAdditionalInputConfig(const UScWInputConfig* InputConfig)
{
	//@TODO: Implement me!
}

bool UScWHeroComponent::IsReadyToBindInputs() const
{
	return bReadyToBindInputs;
}

void UScWHeroComponent::Input_AbilityTagPressed(FGameplayTag InTag)
{
	if (const APawn* Pawn = GetPawn<APawn>())
	{
		if (const UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			if (UScWAbilitySystemComponent* OwnerASC = PawnExtComp->GetScWAbilitySystemComponent())
			{
				OwnerASC->AbilityTagPressed(InTag);
			}
		}	
	}
}

void UScWHeroComponent::Input_AbilityTagReleased(FGameplayTag InTag)
{
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}
	if (const UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (UScWAbilitySystemComponent* OwnerASC = PawnExtComp->GetScWAbilitySystemComponent())
		{
			OwnerASC->AbilityTagReleased(InTag);
		}
	}
}

void UScWHeroComponent::Input_Movement(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	// If the player has attempted to move again then cancel auto running
	/*if (AScWPlayerController* OwnerController = Cast<AScWPlayerController>(Controller))
	{
		OwnerController->SetIsAutoRunning(false);
	}*/
	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UScWHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}
	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

void UScWHeroComponent::Input_LookStick(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	const UWorld* World = GetWorld();
	check(World);

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X * ScWHero::LookYawRate * World->GetDeltaSeconds());
	}
	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y * ScWHero::LookPitchRate * World->GetDeltaSeconds());
	}
}

/*void UScWHeroComponent::Input_Crouch(const FInputActionValue& InputActionValue)
{
	if (AScWCharacter* Character = GetPawn<AScWCharacter>())
	{
		Character->ToggleCrouch();
	}
}*/

/*void UScWHeroComponent::Input_AutoRun(const FInputActionValue& InputActionValue)
{
	if (APawn* Pawn = GetPawn<APawn>())
	{
		if (AScWPlayerController* Controller = Cast<AScWPlayerController>(Pawn->GetController()))
		{
			// Toggle auto running
			Controller->SetIsAutoRunning(!Controller->GetIsAutoRunning());
		}	
	}
}

TSubclassOf<UScWCameraMode> UScWHeroComponent::DetermineCameraMode() const
{
	if (AbilityCameraMode)
	{
		return AbilityCameraMode;
	}

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return nullptr;
	}

	if (UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UScWPawnData* PawnData = PawnExtComp->GetPawnData<UScWPawnData>())
		{
			return PawnData->DefaultCameraMode;
		}
	}

	return nullptr;
}

void UScWHeroComponent::SetAbilityCameraMode(TSubclassOf<UScWCameraMode> CameraMode, const FGameplayAbilitySpecHandle& OwningSpecHandle)
{
	if (CameraMode)
	{
		AbilityCameraMode = CameraMode;
		AbilityCameraModeOwningSpecHandle = OwningSpecHandle;
	}
}

void UScWHeroComponent::ClearAbilityCameraMode(const FGameplayAbilitySpecHandle& OwningSpecHandle)
{
	if (AbilityCameraModeOwningSpecHandle == OwningSpecHandle)
	{
		AbilityCameraMode = nullptr;
		AbilityCameraModeOwningSpecHandle = FGameplayAbilitySpecHandle();
	}
}*/

