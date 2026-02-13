// Scientific Ways

#pragma once

#include "ScWGameCore.h"

//#include "GameAnalytics.h"
//#include "GameAnalyticsModule.h"

#include "Engine/LevelScriptActor.h"

#include "ScWLevelScriptActor.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Level Script Actor"))
class AScWLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	AScWLevelScriptActor();
	
//~ Begin Statics
public:

	UFUNCTION(Category = "Statics", BlueprintCallable)
	static MODULE_API AScWLevelScriptActor* TryGetScWLevelScriptOfActor(const AActor* InActor);
//~ End Statics

//~ Begin Initialize
public:

	//UFUNCTION(Category = "Initialize", BlueprintImplementableEvent, BlueprintAuthorityOnly, meta = (DisplayName = "HandlePreGameSetup (Persistent Level)"))
	//void BP_HandlePreGameSetup_PersistentLevel(class AIDGameMode* InIDGameMode, class AIDGameState* InIDGameState);
	
protected:
	virtual void PostInitializeComponents() override; // AActor
	virtual void BeginPlay() override; // AActor
	virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override; // AActor
//~ End Initialize

//~ Begin Save Game
public:

	//UPROPERTY(Category = "Save Game", EditAnywhere, BlueprintReadWrite)
	//bool bTrySaveGameOnEndPlay;
//~ End Save Game
	
//~ Begin Pawns
public:

	UFUNCTION(Category = "Pawns", BlueprintImplementableEvent, meta = (DisplayName = "OnPawnBeginPlay", KeyWords = "OnCharacterBeginPlay"))
	MODULE_API void BP_OnPawnBeginPlay(APawn* InPawn);

	UFUNCTION(Category = "Pawns", BlueprintImplementableEvent, meta = (DisplayName = "OnPawnControllerChanged", KeyWords = "OnCharacterControllerChanged"))
	MODULE_API void BP_OnPawnControllerChanged(APawn* InPawn, AController* InController);
//~ End Pawns

//~ Begin Players
public:

	UFUNCTION(Category = "Players", BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Choose Player Start"))
	MODULE_API AActor* BP_ChoosePlayerStart(AController* InPlayer) const;
//~ End Players

//~ Begin Events
public:

	UFUNCTION(Category = "Events", BlueprintCallable, BlueprintImplementableEvent, BlueprintAuthorityOnly, meta = (DisplayName = "HandleCustomEvent (ScWLevelScriptActor)", AutoCreateRefTerm = "InEventName", ReturnDisplayName = "OutReturnCode"))
	MODULE_API int32 BP_HandleCustomEvent(const FName& InEventName, UObject* InOptionalObject = nullptr);
//~ End Events

//~ Begin Levels
public:

	UFUNCTION(Category = "Levels", BlueprintCallable, meta = (WorldContext = "InWCO", DisplayName = "LoadStreamLevelArraySync (by Object Reference)"))
	MODULE_API void LoadStreamLevelArraySync(const UObject* InWCO, const TArray<TSoftObjectPtr<UWorld>>& InLevelArray, bool bInMakeVisibleAfterLoad = true);

	UFUNCTION(Category = "Levels", BlueprintCallable, meta = (WorldContext = "InWCO", DisplayName = "UnLoadStreamLevelArraySync (by Object Reference)"))
	MODULE_API void UnLoadStreamLevelArraySync(const UObject* InWCO, const TArray<TSoftObjectPtr<UWorld>>& InLevelArray);
//~ End Levels

//~ Begin Audio
public:

	UFUNCTION(Category = "Audio", BlueprintCallable, meta = (AutoCreateRefTerm = "InLayer", InLayer = "Default"))
	MODULE_API UAudioComponent* GetSound2D_AtLayer(const FName& InLayer) const { return AudioLayerMap.Contains(InLayer) ? AudioLayerMap[InLayer] : nullptr; }

	UFUNCTION(Category = "Audio", BlueprintCallable, meta = (AutoCreateRefTerm = "InLayer", InLayer = "Default", AdvancedDisplay = "InPitchMultiplier, InStartTime, InConcurrencySettings, bInAutoDestroy"))
	MODULE_API UAudioComponent* PlaySound2D_AtLayer(const FName& InLayer, USoundBase* InSoundAsset, float InFadeInDuration = 0.0f, float InVolumeMultiplier = 1.0f, float InPitchMultiplier = 1.0f, float InStartTime = 0.0f, USoundConcurrency* InConcurrencySettings = nullptr, bool bInAutoDestroy = true);

	UFUNCTION(Category = "Audio", BlueprintCallable, meta = (AutoCreateRefTerm = "InLayer", InLayer = "Default"))
	MODULE_API bool StopSound2D_AtLayer(const FName& InLayer, float InFadeOutDuration = 1.0);

protected:
	void OnAudioComponentFinished(UAudioComponent* InAudioComponent);

	UPROPERTY(Category = "Audio", VisibleInstanceOnly, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAudioComponent>> AudioLayerMap;
//~ End Audio
	
//~ Begin Analytics
public:

	/*UFUNCTION(Category = "Analytics", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Get Default Analytics Chapter Name"))
	MODULE_API FString BP_GetDefaultAnalyticsChapterName() const;

	UFUNCTION(Category = "Analytics", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Get Default Analytics Map Name"))
	MODULE_API FString BP_GetDefaultAnalyticsMapName() const;

	UFUNCTION(Category = "Analytics", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Get Default Analytics Location Name"))
	MODULE_API FString BP_GetDefaultAnalyticsLocationName(const FVector& InLocation) const;

	UFUNCTION(Category = "Analytics", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Send Level Start Analytics Event", AutoCreateRefTerm = "InEventLocation"))
	MODULE_API void BP_SendLevelProgressionAnalyticsEvent(EGAProgressionStatus InType, const FVector& InEventLocation, const bool bInSendEventLocation = false) const;

	UFUNCTION(Category = "Analytics", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Send Default Design Analytics Event"))
	MODULE_API void BP_SendDefaultDesignAnalyticsEvent(const FString& InEvent) const;

	UPROPERTY(Category = "Analytics", EditAnywhere, BlueprintReadWrite)
	bool bSendBeginPlayDesignEvent;

	UPROPERTY(Category = "Analytics", EditAnywhere, BlueprintReadWrite)
	bool bSendEndPlayDesignEvent;*/
//~ End Analytics
};

#undef MODULE_API
