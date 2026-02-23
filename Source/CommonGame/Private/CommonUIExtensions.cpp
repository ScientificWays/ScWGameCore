// Scientific Ways

#include "CommonUIExtensions.h"

#include "CommonInputSubsystem.h"
#include "CommonLocalPlayer.h"
#include "Engine/GameInstance.h"
#include "GameUIManagerSubsystem.h"
#include "GameUIPolicy.h"
#include "PrimaryGameLayout.h"

#include "GameFramework/PlayerState.h"

#include "Kismet/GameplayStatics.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonUIExtensions)

int32 UCommonUIExtensions::InputSuspensions = 0;

const ULocalPlayer* UCommonUIExtensions::GetLocalPlayerFromContext(const UObject* InPlayerContext)
{
	if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(InPlayerContext))
	{
		return LocalPlayer;
	}
	else if (const APlayerController* PlayerController = Cast<APlayerController>(InPlayerContext))
	{
		return PlayerController->GetLocalPlayer();
	}
	else if (const APlayerState* PlayerState = Cast<APlayerState>(InPlayerContext))
	{
		return GetLocalPlayerFromContext(PlayerState->GetOwningController());
	}
	else if (const APawn* Pawn = Cast<APawn>(InPlayerContext))
	{
		return GetLocalPlayerFromContext(Pawn->GetController());
	}
	else if (const UWidget* Widget = Cast<UWidget>(InPlayerContext))
	{
		return Widget->GetOwningLocalPlayer();
	}
	else if (const UActorComponent* ActorComponent = Cast<UActorComponent>(InPlayerContext))
	{
		return GetLocalPlayerFromContext(ActorComponent->GetOwner());
	}
	/*else if (const UObject* Outer = InPlayerContext->GetOuter())
	{
		return GetLocalPlayerFromContext(Outer);
	}*/
	else
	{
		return nullptr;
	}
}

ECommonInputType UCommonUIExtensions::GetOwningPlayerInputType(const UObject* InPlayerContext)
{
	if (const UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(GetLocalPlayerFromContext(InPlayerContext)))
	{
		return InputSubsystem->GetCurrentInputType();
	}
	return ECommonInputType::Count;
}

ECommonInputType UCommonUIExtensions::SwitchOnPlayerInputType(const UObject* InPlayerContext)
{
	return GetOwningPlayerInputType(InPlayerContext);
}

bool UCommonUIExtensions::IsOwningPlayerUsingTouch(const UObject* InPlayerContext)
{
	return GetOwningPlayerInputType(InPlayerContext) == ECommonInputType::Touch;
}

bool UCommonUIExtensions::IsOwningPlayerUsingGamepad(const UObject* InPlayerContext)
{
	return GetOwningPlayerInputType(InPlayerContext) == ECommonInputType::Gamepad;
}

UCommonActivatableWidget* UCommonUIExtensions::PushContentToLayer_ForPlayer(const ULocalPlayer* InLocalPlayer, FGameplayTag InLayerName, TSubclassOf<UCommonActivatableWidget> InWidgetClass)
{
	if (!ensure(InLocalPlayer) || !ensure(InWidgetClass != nullptr))
	{
		return nullptr;
	}
	if (UGameUIManagerSubsystem* UIManager = InLocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(InLocalPlayer)))
			{
				return RootLayout->PushWidgetToLayerStack<UCommonActivatableWidget>(InLayerName, InWidgetClass);
			}
		}
	}
	ensure(false);
	return nullptr;
}

/*UCommonActivatableWidget* UCommonUIExtensions::PushContentToLayerAndInit_ForPlayer(const ULocalPlayer* InLocalPlayer, FGameplayTag InLayerName, TSubclassOf<UCommonActivatableWidget> InWidgetClass, FCommonUIInitInstanceSignature InInitInstanceFunc)
{
	if (!ensure(InLocalPlayer) || !ensure(InWidgetClass != nullptr))
	{
		return nullptr;
	}
	if (UGameUIManagerSubsystem* UIManager = InLocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(InLocalPlayer)))
			{
				return RootLayout->PushWidgetToLayerStack<UCommonActivatableWidget>(InLayerName, InWidgetClass, [&InInitInstanceFunc](UCommonActivatableWidget& InWidget)
				{
					InInitInstanceFunc.ExecuteIfBound(&InWidget);
				});
			}
		}
	}
	ensure(false);
	return nullptr;
}*/

void UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(const ULocalPlayer* InLocalPlayer, FGameplayTag InLayerName, TSoftClassPtr<UCommonActivatableWidget> InWidgetClass)
{
	if (!ensure(InLocalPlayer) || !ensure(!InWidgetClass.IsNull()))
	{
		return;
	}
	if (UGameUIManagerSubsystem* UIManager = InLocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(InLocalPlayer)))
			{
				const bool bSuspendInputUntilComplete = true;
				RootLayout->PushWidgetToLayerStackAsync(InLayerName, bSuspendInputUntilComplete, InWidgetClass);
				return;
			}
		}
	}
	ensure(false);
}

void UCommonUIExtensions::PopContentFromLayer(UCommonActivatableWidget* InActivatableWidget)
{
	if (!InActivatableWidget)
	{
		// Ignore request to pop an already deleted widget
		ensure(false);
		return;
	}
	if (const ULocalPlayer* LocalPlayer = InActivatableWidget->GetOwningLocalPlayer())
	{
		if (const UGameUIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
		{
			if (const UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
			{
				if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(LocalPlayer)))
				{
					RootLayout->FindAndRemoveWidgetFromLayer(InActivatableWidget);
					return;
				}
			}
		}
	}
	ensure(false);
}

ULocalPlayer* UCommonUIExtensions::GetLocalPlayerFromController(APlayerController* PlayerController)
{
	if (PlayerController)
	{
		return Cast<ULocalPlayer>(PlayerController->Player);
	}
	ensure(false);
	return nullptr;
}

FName UCommonUIExtensions::SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason)
{
	return SuspendInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendReason);
}

FName UCommonUIExtensions::SuspendInputForPlayer(ULocalPlayer* InLocalPlayer, FName SuspendReason)
{
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(InLocalPlayer))
	{
		InputSuspensions++;
		FName SuspendToken = SuspendReason;
		SuspendToken.SetNumber(InputSuspensions);

		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, true);

		return SuspendToken;
	}
	ensure(false);
	return NAME_None;
}

void UCommonUIExtensions::ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken)
{
	ResumeInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendToken);
}

void UCommonUIExtensions::ResumeInputForPlayer(ULocalPlayer* InLocalPlayer, FName SuspendToken)
{
	if (SuspendToken == NAME_None)
	{
		return;
	}
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(InLocalPlayer))
	{
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, false);
		return;
	}
	ensure(false);
	return;
}

