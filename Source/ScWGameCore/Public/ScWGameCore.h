// Scientific Ways

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"

#include "Misc/CommandLine.h"

#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "Engine/GameInstance.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "GameplayTagAssetInterface.h"
#include "GenericTeamAgentInterface.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/GameFrameworkComponentManager.h"

#include "GameFramework/Actor.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameState.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/CheatManager.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Net/UnrealNetwork.h"
#include "Engine/NetConnection.h"

#include "InputAction.h"
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Utils/ScWUtils.h"

DECLARE_LOG_CATEGORY_EXTERN(LogScWGameCore, Log, All);

class FScWGameCoreModule : public IModuleInterface
{
public:
	virtual void StartupModule() override; // IModuleInterface
	virtual void ShutdownModule() override; // IModuleInterface
};
