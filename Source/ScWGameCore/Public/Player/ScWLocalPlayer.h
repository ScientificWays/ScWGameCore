// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "CommonLocalPlayer.h"
#include "Team/ScWTeamAgentInterface.h"

#include "ScWLocalPlayer.generated.h"

#define MODULE_API SCWGAMECORE_API

struct FGenericTeamId;

class APlayerController;
class UInputMappingContext;
class UScWSettingsLocal;
class UScWSettingsShared;
class UObject;
class UWorld;
struct FFrame;
struct FSwapAudioOutputResult;

/**
 *	UScWLocalPlayer
 */
UCLASS(MinimalAPI)
class UScWLocalPlayer : public UCommonLocalPlayer, public IScWTeamAgentInterface
{
	GENERATED_BODY()

public:
	MODULE_API UScWLocalPlayer();

public:
	//~UObject interface
	MODULE_API virtual void PostInitProperties() override;
	//~End of UObject interface

	//~UPlayer interface
	MODULE_API virtual void SwitchController(class APlayerController* PC) override;
	//~End of UPlayer interface

	//~ULocalPlayer interface
	MODULE_API virtual bool SpawnPlayActor(const FString& URL, FString& OutError, UWorld* InWorld) override;
	MODULE_API virtual void InitOnlineSession() override;
	//~End of ULocalPlayer interface

private:

	UPROPERTY()
	TWeakObjectPtr<APlayerController> LastBoundPC;
	
//~ Begin Team
public:
	MODULE_API virtual FGenericTeamId GetGenericTeamId() const override; // IGenericTeamAgentInterface
	MODULE_API virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override; // IGenericTeamAgentInterface

	MODULE_API virtual const FGameplayTag& GetTeamTag() const override; // IScWTeamAgentInterface
	MODULE_API virtual void SetTeamTag(const FGameplayTag& InTeamTag) override; // IScWTeamAgentInterface
	MODULE_API virtual FOnScWTeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() override; // IScWTeamAgentInterface
private:

	UFUNCTION()
	void OnControllerChangedTeam(UObject* TeamAgent, const FGameplayTag& InPrevTeamTag, const FGameplayTag& InNewTeamTag);

	UPROPERTY()
	FOnScWTeamIndexChangedDelegate OnTeamChangedDelegate;
//~ End Team

//~ Begin Settings
public:

	/** Gets the local settings for this player, this is read from config files at process startup and is always valid */
	UFUNCTION()
	MODULE_API UScWSettingsLocal* GetLocalSettings() const;

	/** Gets the shared setting for this player, this is read using the save game system so may not be correct until after user login */
	UFUNCTION()
	MODULE_API UScWSettingsShared* GetSharedSettings() const;

	/** Starts an async request to load the shared settings, this will call OnSharedSettingsLoaded after loading or creating new ones */
	MODULE_API void LoadSharedSettingsFromDisk(bool bForceLoad = false);

protected:
	MODULE_API void OnSharedSettingsLoaded(UScWSettingsShared* LoadedOrCreatedSettings);

	MODULE_API void OnAudioOutputDeviceChanged(const FString& InAudioOutputDeviceId);
	
	UFUNCTION()
	MODULE_API void OnCompletedAudioDeviceSwap(const FSwapAudioOutputResult& SwapResult);

	MODULE_API void OnPlayerControllerChanged(APlayerController* NewController);

private:

	UPROPERTY(Transient)
	mutable TObjectPtr<UScWSettingsShared> SharedSettings;

	FUniqueNetIdRepl NetIdForSharedSettings;

	UPROPERTY(Transient)
	mutable TObjectPtr<const UInputMappingContext> InputMappingContext;
//~ End Settings
};

#undef MODULE_API
