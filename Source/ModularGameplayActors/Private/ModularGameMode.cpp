// Scientific Ways

#include "ModularGameMode.h"

#include "ModularGameState.h"
#include "ModularPawn.h"
#include "ModularPlayerController.h"
#include "ModularPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ModularGameMode)

AModularGameModeBase::AModularGameModeBase(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	GameStateClass = AModularGameStateBase::StaticClass();
	PlayerControllerClass = AModularPlayerController::StaticClass();
	PlayerStateClass = AModularPlayerState::StaticClass();
	DefaultPawnClass = AModularPawn::StaticClass();
}

AModularGameMode::AModularGameMode(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	GameStateClass = AModularGameState::StaticClass();
	PlayerControllerClass = AModularPlayerController::StaticClass();
	PlayerStateClass = AModularPlayerState::StaticClass();
	DefaultPawnClass = AModularPawn::StaticClass();
}

