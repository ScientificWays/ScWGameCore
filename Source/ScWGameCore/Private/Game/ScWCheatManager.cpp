// Scientific Ways

#include "Game/ScWCheatManager.h"

#include "Tags/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "System/ScWGameData.h"
#include "System/ScWAssetManager.h"

#include "Player/ScWPlayerController.h"
#include "Player/ScWDebugCameraController.h"

//#include "System/ScWSystemStatics.h"

#include "Development/ScWDeveloperSettings.h"

#include "GameFramework/Pawn.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Console.h"
#include "GameFramework/HUD.h"
#include "AbilitySystemGlobals.h"
#include "Damage/ScWAttributeHealthComponent.h"
#include "Character/ScWPawnExtensionComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWCheatManager)

DEFINE_LOG_CATEGORY(LogScWCheat);

namespace ScWCheat
{
	static const FName NAME_Fixed = FName(TEXT("Fixed"));
	
	static bool bEnableDebugCameraCycling = false;
	static FAutoConsoleVariableRef CVarEnableDebugCameraCycling(
		TEXT("ScWCheat.EnableDebugCameraCycling"),
		bEnableDebugCameraCycling,
		TEXT("If true then you can cycle the debug camera while running the game."),
		ECVF_Cheat);

	static bool bStartInGodMode = false;
	static FAutoConsoleVariableRef CVarStartInGodMode(
		TEXT("ScWCheat.StartInGodMode"),
		bStartInGodMode,
		TEXT("If true then the God cheat will be applied on begin play"),
		ECVF_Cheat);
};


UScWCheatManager::UScWCheatManager()
{
	DebugCameraControllerClass = AScWDebugCameraController::StaticClass();
}

void UScWCheatManager::InitCheatManager()
{
	Super::InitCheatManager();

#if WITH_EDITOR
	if (GIsEditor)
	{
		APlayerController* PC = GetOuterAPlayerController();
		for (const FScWCheatToRun& CheatRow : GetDefault<UScWDeveloperSettings>()->CheatsToRun)
		{
			if (CheatRow.Phase == ECheatExecutionTime::OnCheatManagerCreated)
			{
				PC->ConsoleCommand(CheatRow.Cheat, /*bWriteToLog=*/ true);
			}
		}
	}
#endif

	if (ScWCheat::bStartInGodMode)
	{
		God();	
	}
}

void UScWCheatManager::CheatOutputText(const FString& TextToOutput)
{
#if USING_CHEAT_MANAGER
	// Output to the console.
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->ViewportConsole)
	{
		GEngine->GameViewport->ViewportConsole->OutputText(TextToOutput);
	}

	// Output to log.
	UE_LOG(LogScWCheat, Display, TEXT("%s"), *TextToOutput);
#endif // USING_CHEAT_MANAGER
}

void UScWCheatManager::Cheat(const FString& Msg)
{
	if (AScWPlayerController* TargetPC = Cast<AScWPlayerController>(GetOuterAPlayerController()))
	{
		TargetPC->Server_Cheat(Msg.Left(128));
	}
}

void UScWCheatManager::CheatAll(const FString& Msg)
{
	if (AScWPlayerController* TargetPC = Cast<AScWPlayerController>(GetOuterAPlayerController()))
	{
		TargetPC->Server_CheatAll(Msg.Left(128));
	}
}

/*void UScWCheatManager::PlayNextGame()
{
	UScWSystemStatics::PlayNextGame(this);
}*/

void UScWCheatManager::EnableDebugCamera()
{
	Super::EnableDebugCamera();
}

void UScWCheatManager::DisableDebugCamera()
{
	FVector DebugCameraLocation;
	FRotator DebugCameraRotation;

	ADebugCameraController* DebugCC = Cast<ADebugCameraController>(GetOuter());
	APlayerController* OriginalPC = nullptr;

	if (DebugCC)
	{
		OriginalPC = DebugCC->OriginalControllerRef;
		DebugCC->GetPlayerViewPoint(DebugCameraLocation, DebugCameraRotation);
	}

	Super::DisableDebugCamera();

	if (OriginalPC && OriginalPC->PlayerCameraManager && (OriginalPC->PlayerCameraManager->CameraStyle == ScWCheat::NAME_Fixed))
	{
		OriginalPC->SetInitialLocationAndRotation(DebugCameraLocation, DebugCameraRotation);

		OriginalPC->PlayerCameraManager->ViewTarget.POV.Location = DebugCameraLocation;
		OriginalPC->PlayerCameraManager->ViewTarget.POV.Rotation = DebugCameraRotation;
		OriginalPC->PlayerCameraManager->PendingViewTarget.POV.Location = DebugCameraLocation;
		OriginalPC->PlayerCameraManager->PendingViewTarget.POV.Rotation = DebugCameraRotation;
	}
}

bool UScWCheatManager::InDebugCamera() const
{
	return (Cast<ADebugCameraController>(GetOuter()) ? true : false);
}

void UScWCheatManager::EnableFixedCamera()
{
	const ADebugCameraController* DebugCC = Cast<ADebugCameraController>(GetOuter());
	APlayerController* PC = (DebugCC ? ToRawPtr(DebugCC->OriginalControllerRef) : GetOuterAPlayerController());

	if (PC && PC->PlayerCameraManager)
	{
		PC->SetCameraMode(ScWCheat::NAME_Fixed);
	}
}

void UScWCheatManager::DisableFixedCamera()
{
	const ADebugCameraController* DebugCC = Cast<ADebugCameraController>(GetOuter());
	APlayerController* PC = (DebugCC ? ToRawPtr(DebugCC->OriginalControllerRef) : GetOuterAPlayerController());

	if (PC && PC->PlayerCameraManager)
	{
		PC->SetCameraMode(NAME_Default);
	}
}

bool UScWCheatManager::InFixedCamera() const
{
	const ADebugCameraController* DebugCC = Cast<ADebugCameraController>(GetOuter());
	const APlayerController* PC = (DebugCC ? ToRawPtr(DebugCC->OriginalControllerRef) : GetOuterAPlayerController());

	if (PC && PC->PlayerCameraManager)
	{
		return (PC->PlayerCameraManager->CameraStyle == ScWCheat::NAME_Fixed);
	}

	return false;
}

void UScWCheatManager::ToggleFixedCamera()
{
	if (InFixedCamera())
	{
		DisableFixedCamera();
	}
	else
	{
		EnableFixedCamera();
	}
}

void UScWCheatManager::CycleDebugCameras()
{
	if (!ScWCheat::bEnableDebugCameraCycling)
	{
		return;
	}
	
	if (InDebugCamera())
	{
		EnableFixedCamera();
		DisableDebugCamera();
	}
	else if (InFixedCamera())
	{
		DisableFixedCamera();
		DisableDebugCamera();
	}
	else
	{
		EnableDebugCamera();
		DisableFixedCamera();
	}
}

void UScWCheatManager::CycleAbilitySystemDebug()
{
	APlayerController* PC = Cast<APlayerController>(GetOuterAPlayerController());

	if (PC && PC->MyHUD)
	{
		if (!PC->MyHUD->bShowDebugInfo || !PC->MyHUD->DebugDisplay.Contains(TEXT("AbilitySystem")))
		{
			PC->MyHUD->ShowDebug(TEXT("AbilitySystem"));
		}

		PC->ConsoleCommand(TEXT("AbilitySystem.Debug.NextCategory"));
	}
}

void UScWCheatManager::CancelActivatedAbilities()
{
	if (UScWAbilitySystemComponent* TargetASC = GetPlayerAbilitySystemComponent())
	{
		const bool bReplicateCancelAbility = true;
		TargetASC->CancelInputActivatedAbilities(bReplicateCancelAbility);
	}
}

void UScWCheatManager::AddTagToSelf(FString TagName)
{
	FGameplayTag Tag = FScWCoreTags::FindTagByString(TagName, true);
	if (Tag.IsValid())
	{
		if (UScWAbilitySystemComponent* TargetASC = GetPlayerAbilitySystemComponent())
		{
			TargetASC->AddDynamicTagGameplayEffect(Tag);
		}
	}
	else
	{
		UE_LOG(LogScWCheat, Display, TEXT("AddTagToSelf: Could not find any tag matching [%s]."), *TagName);
	}
}

void UScWCheatManager::RemoveTagFromSelf(FString TagName)
{
	FGameplayTag Tag = FScWCoreTags::FindTagByString(TagName, true);
	if (Tag.IsValid())
	{
		if (UScWAbilitySystemComponent* TargetASC = GetPlayerAbilitySystemComponent())
		{
			TargetASC->RemoveDynamicTagGameplayEffect(Tag);
		}
	}
	else
	{
		UE_LOG(LogScWCheat, Display, TEXT("RemoveTagFromSelf: Could not find any tag matching [%s]."), *TagName);
	}
}

void UScWCheatManager::DamageSelf(float DamageAmount)
{
	if (UScWAbilitySystemComponent* TargetASC = GetPlayerAbilitySystemComponent())
	{
		ApplySetByCallerDamage(TargetASC, DamageAmount);
	}
}

void UScWCheatManager::DamageTarget(float DamageAmount)
{
	if (AScWPlayerController* TargetPC = Cast<AScWPlayerController>(GetOuterAPlayerController()))
	{
		if (TargetPC->GetNetMode() == NM_Client)
		{
			// Automatically send cheat to server for convenience.
			TargetPC->Server_Cheat(FString::Printf(TEXT("DamageTarget %.2f"), DamageAmount));
			return;
		}
		FHitResult TargetHitResult;
		AActor* TargetActor = GetTarget(TargetPC, TargetHitResult);

		if (UScWAbilitySystemComponent* TargetASC = Cast<UScWAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor)))
		{
			ApplySetByCallerDamage(TargetASC, DamageAmount);
		}
	}
}

void UScWCheatManager::ApplySetByCallerDamage(UScWAbilitySystemComponent* InTargetASC, float InDamageAmount)
{
	check(InTargetASC);

	TSubclassOf<UGameplayEffect> DamageGE = UScWAssetManager::GetSubclass(UScWGameData::Get().DamageGameplayEffect_SetByCaller);
	FGameplayEffectSpecHandle SpecHandle = InTargetASC->MakeOutgoingSpec(DamageGE, 1.0f, InTargetASC->MakeEffectContext());

	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(FScWCoreTags::SetByCaller_Magnitude, -InDamageAmount);
		InTargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UScWCheatManager::HealSelf(float InHealAmount)
{
	if (UScWAbilitySystemComponent* TargetASC = GetPlayerAbilitySystemComponent())
	{
		ApplySetByCallerHeal(TargetASC, InHealAmount);
	}
}

void UScWCheatManager::HealTarget(float InHealAmount)
{
	if (AScWPlayerController* TargetPC = Cast<AScWPlayerController>(GetOuterAPlayerController()))
	{
		FHitResult TargetHitResult;
		AActor* TargetActor = GetTarget(TargetPC, TargetHitResult);

		if (UScWAbilitySystemComponent* TargetASC = UScWAbilitySystemComponent::TryGetFromActor(TargetActor))
		{
			ApplySetByCallerHeal(TargetASC, InHealAmount);
		}
	}
}

void UScWCheatManager::ApplySetByCallerHeal(UScWAbilitySystemComponent* InTargetASC, float InHealAmount)
{
	check(InTargetASC);

	TSubclassOf<UGameplayEffect> HealGE = UScWAssetManager::GetSubclass(UScWGameData::Get().HealGameplayEffect_SetByCaller);
	FGameplayEffectSpecHandle SpecHandle = InTargetASC->MakeOutgoingSpec(HealGE, 1.0f, InTargetASC->MakeEffectContext());

	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(FScWCoreTags::SetByCaller_Magnitude, InHealAmount);
		InTargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

UScWAbilitySystemComponent* UScWCheatManager::GetPlayerAbilitySystemComponent() const
{
	if (AScWPlayerController* TargetPC = Cast<AScWPlayerController>(GetOuterAPlayerController()))
	{
		return UScWAbilitySystemComponent::TryGetFromActor(TargetPC);
	}
	return nullptr;
}

/*void UScWCheatManager::DamageSelfDestruct()
{
	if (AScWPlayerController* TargetPC = Cast<AScWPlayerController>(GetOuterAPlayerController()))
	{
 		if (const UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::GetPawnExtensionComponent(TargetPC->GetPawn()))
		{
			if (PawnExtComp->HasReachedInitState(FScWCoreTags::InitState_GameplayReady))
			{
				if (UScWHealthComponent* HealthComponent = UScWHealthComponent::FindHealthComponent(TargetPC->GetPawn()))
				{
					//HealthComponent->DamageSelfDestruct();
				}
			}
		}
	}
}*/

void UScWCheatManager::God()
{
	if (AScWPlayerController* TargetPC = Cast<AScWPlayerController>(GetOuterAPlayerController()))
	{
		if (TargetPC->GetNetMode() == NM_Client)
		{
			// Automatically send cheat to server for convenience.
			TargetPC->Server_Cheat(FString::Printf(TEXT("God")));
			return;
		}

		if (UScWAbilitySystemComponent* TargetASC = UScWAbilitySystemComponent::TryGetFromActor(TargetPC))
		{
			const FGameplayTag Tag = FScWCoreTags::Cheat_Invulnerable;
			const bool bHasTag = TargetASC->HasMatchingGameplayTag(Tag);

			if (bHasTag)
			{
				TargetASC->RemoveDynamicTagGameplayEffect(Tag);
			}
			else
			{
				TargetASC->AddDynamicTagGameplayEffect(Tag);
			}
		}
	}
}

void UScWCheatManager::UnlimitedHealth(int32 Enabled)
{
	if (UScWAbilitySystemComponent* TargetASC = GetPlayerAbilitySystemComponent())
	{
		const FGameplayTag Tag = FScWCoreTags::Cheat_UnlimitedHealth;
		const bool bHasTag = TargetASC->HasMatchingGameplayTag(Tag);

		if ((Enabled == -1) || ((Enabled > 0) && !bHasTag) || ((Enabled == 0) && bHasTag))
		{
			if (bHasTag)
			{
				TargetASC->RemoveDynamicTagGameplayEffect(Tag);
			}
			else
			{
				TargetASC->AddDynamicTagGameplayEffect(Tag);
			}
		}
	}
}

