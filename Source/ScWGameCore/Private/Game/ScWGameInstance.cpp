// Scientific Ways

#include "Game/ScWGameInstance.h"

#include "Tags/ScWCoreTags.h"

#include "Components/GameFrameworkComponentManager.h"

//#include "GameAnalytics.h"
//#include "GameAnalyticsModule.h"

UScWGameInstance::UScWGameInstance(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	
}

//~ Begin Initialize
void UScWGameInstance::Init() // UGameInstance
{
	Super::Init();

	/*if (bInitGameAnalytics)
	{
		BP_InitGameAnalytics();
	}*/

	// Register custom init states
	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>(this);
	if (ensure(ComponentManager))
	{
		ComponentManager->RegisterInitState(FScWCoreTags::InitState_Spawned, false, FGameplayTag());
		ComponentManager->RegisterInitState(FScWCoreTags::InitState_DataAvailable, false, FScWCoreTags::InitState_Spawned);
		ComponentManager->RegisterInitState(FScWCoreTags::InitState_DataInitialized, false, FScWCoreTags::InitState_DataAvailable);
		ComponentManager->RegisterInitState(FScWCoreTags::InitState_GameplayReady, false, FScWCoreTags::InitState_DataInitialized);
	}
}

void UScWGameInstance::Shutdown() // UGameInstance
{
	Super::Shutdown();


}
//~ End Initialize

//~ Begin Analytics
/*UGameAnalytics* UScWGameInstance::BP_InitGameAnalytics_Implementation()
{
	UGameAnalytics* GameAnalytics = FGameAnalyticsModule::Get().GetInstance();

	GameAnalytics->Initialize(GameAnalyticsSettings.GameKey, GameAnalyticsSettings.SecretKey);
	GameAnalytics->ConfigureBuild(GameAnalyticsSettings.Build);

	GameAnalytics->SetEnabledEventSubmission(GameAnalyticsSettings.bEnableEventSubmission);

	GameAnalytics->ConfigureAvailableCustomDimensions01(GameAnalyticsSettings.CustomDimensions01);
	GameAnalytics->ConfigureAvailableCustomDimensions02(GameAnalyticsSettings.CustomDimensions02);
	GameAnalytics->ConfigureAvailableCustomDimensions03(GameAnalyticsSettings.CustomDimensions03);

	GameAnalytics->ConfigureAvailableResourceCurrencies(GameAnalyticsSettings.ResourceCurrencies);
	GameAnalytics->ConfigureAvailableResourceItemTypes(GameAnalyticsSettings.ResourceItemTypes);

	GameAnalytics->SetEnabledManualSessionHandling(GameAnalyticsSettings.bUseManualSessionHandling);
	GameAnalytics->ConfigureAutoDetectAppVersion(GameAnalyticsSettings.bAutoDetectAppVersion);

	if (GameAnalyticsSettings.bDisableDeviceInfo)
	{
		GameAnalytics->DisableDeviceInfo();
	}
	GameAnalytics->SetEnabledErrorReporting(GameAnalyticsSettings.bUseErrorReporting);

	GameAnalytics->EnableFpsHistogram(GameAnalyticsSettings.bEnableFpsHistogram);
	GameAnalytics->EnableMemoryHistogram(GameAnalyticsSettings.bEnableMemoryHistogram);
	GameAnalytics->EnableHealthHardwareInfo(GameAnalyticsSettings.bEnableHealthHardwareInfo);

	GameAnalytics->SetEnabledInfoLog(GameAnalyticsSettings.bInfoLogBuild);
	GameAnalytics->SetEnabledVerboseLog(GameAnalyticsSettings.bVerboseLogBuild);
	return GameAnalytics;
}*/
//~ End Analytics
