// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ModularGameMode.h"

#include "ScWGameMode.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *	Post login event, triggered when a player or bot joins the game as well as after seamless and non seamless travel
 *	This is called after the player has finished initialization
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScWGameModePlayerInitialized, AGameModeBase* /*GameMode*/, AController* /*NewPlayer*/);

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Game Mode"))
class AScWGameMode : public AModularGameModeBase
{
	GENERATED_BODY()

public:

	AScWGameMode(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "ScW | Pawn")
	MODULE_API const class UScWPawnData* GetPawnDataForController(const AController* InController) const;

//~AGameModeBase interface
	MODULE_API virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override; // AGameModeBase
	MODULE_API virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override; // AGameModeBase
	MODULE_API virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* InNewPlayer, const FTransform& InSpawnTransform) override; // AGameModeBase
	MODULE_API virtual bool ShouldSpawnAtStartSpot(AController* Player) override; // AGameModeBase
	MODULE_API virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override; // AGameModeBase
	MODULE_API virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override; // AGameModeBase
	MODULE_API virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override; // AGameModeBase
	MODULE_API virtual bool PlayerCanRestart_Implementation(APlayerController* InPlayerController) override; // AGameModeBase
	MODULE_API virtual void InitGameState() override; // AGameModeBase
	MODULE_API virtual bool UpdatePlayerStartSpot(AController* Player, const FString& Portal, FString& OutErrorMessage) override; // AGameModeBase
	MODULE_API virtual void GenericPlayerInitialization(AController* NewPlayer) override; // AGameModeBase
	MODULE_API virtual void FailedToRestartPlayer(AController* NewPlayer) override; // AGameModeBase
//~End of AGameModeBase interface

	// Restart (respawn) the specified player or bot next frame
	// - If bForceReset is true, the controller will be reset this frame (abandoning the currently possessed pawn, if any)
	UFUNCTION(BlueprintCallable)
	MODULE_API void RequestPlayerRestartNextFrame(AController* InController, bool bForceReset = false);

	// Agnostic version of PlayerCanRestart that can be used for both player bots and players
	MODULE_API virtual bool ControllerCanRestart(AController* InController);

	// Delegate called on player initialization, described above
	FOnScWGameModePlayerInitialized OnGameModePlayerInitialized;

protected:
	MODULE_API void OnExperienceLoaded(const class UScWExperience* CurrentExperience);
	MODULE_API bool IsExperienceLoaded() const;

	MODULE_API void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource);

	MODULE_API void HandleMatchAssignmentIfNotExpectingOne();

	//MODULE_API bool TryDedicatedServerLogin();
	//MODULE_API void HostDedicatedServerMatch(ECommonSessionOnlineMode OnlineMode);

	//UFUNCTION()
	//MODULE_API void OnUserInitializedForDedicatedServer(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error, ECommonUserPrivilege RequestedPrivilege, ECommonUserOnlineContext OnlineContext);
};

#undef MODULE_API
