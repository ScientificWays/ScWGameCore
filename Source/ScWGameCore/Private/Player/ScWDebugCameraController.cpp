// Scientific Ways

#include "Player/ScWDebugCameraController.h"

#include "Game/ScWCheatManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWDebugCameraController)

AScWDebugCameraController::AScWDebugCameraController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Use the same cheat class as ScWPlayerController to allow toggling the debug camera through cheats.
	CheatClass = UScWCheatManager::StaticClass();
}

void AScWDebugCameraController::AddCheats(bool bForce)
{
	// Mirrors ScWPlayerController's AddCheats() to avoid the player becoming stuck in the debug camera.
#if USING_CHEAT_MANAGER
	Super::AddCheats(true);
#else //#if USING_CHEAT_MANAGER
	Super::AddCheats(bForce);
#endif // #else //#if USING_CHEAT_MANAGER
}

