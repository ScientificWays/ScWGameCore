// Scientific Ways

#pragma once

#include "Engine/World.h"

#include "GameUIPolicy.generated.h"

#define MODULE_API COMMONGAME_API

class UCommonLocalPlayer;
class UGameUIManagerSubsystem;
class ULocalPlayer;
class UPrimaryGameLayout;

/**
 * 
 */
UENUM()
enum class ELocalMultiplayerInteractionMode : uint8
{
	// Fullscreen viewport for the primary player only, regardless of the other player's existence
	PrimaryOnly,

	// Fullscreen viewport for one player, but players can swap control over who's is displayed and who's is dormant
	SingleToggle,

	// Viewports displayed simultaneously for both players
	Simultaneous
};

USTRUCT()
struct FRootViewportLayoutInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> LocalPlayer = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UPrimaryGameLayout> RootLayout = nullptr;

	UPROPERTY(Transient)
	bool bAddedToViewport = false;

	FRootViewportLayoutInfo() {}
	FRootViewportLayoutInfo(ULocalPlayer* InLocalPlayer, UPrimaryGameLayout* InRootLayout, bool bIsInViewport)
		: LocalPlayer(InLocalPlayer)
		, RootLayout(InRootLayout)
		, bAddedToViewport(bIsInViewport)
	{}

	bool operator==(const ULocalPlayer* OtherLocalPlayer) const { return LocalPlayer == OtherLocalPlayer; }
};

UCLASS(MinimalAPI, Abstract, Blueprintable, Within = GameUIManagerSubsystem)
class UGameUIPolicy : public UObject
{
	GENERATED_BODY()

public:
	template <typename GameUIPolicyClass = UGameUIPolicy>
	static GameUIPolicyClass* GetGameUIPolicyAs(const UObject* WorldContextObject)
	{
		return Cast<GameUIPolicyClass>(GetGameUIPolicy(WorldContextObject));
	}

	static MODULE_API UGameUIPolicy* GetGameUIPolicy(const UObject* WorldContextObject);

public:
	MODULE_API virtual UWorld* GetWorld() const override;
	MODULE_API UGameUIManagerSubsystem* GetOwningUIManager() const;
	MODULE_API UPrimaryGameLayout* GetRootLayout(const UCommonLocalPlayer* LocalPlayer) const;

	ELocalMultiplayerInteractionMode GetLocalMultiplayerInteractionMode() const { return LocalMultiplayerInteractionMode; }

	MODULE_API void RequestPrimaryControl(UPrimaryGameLayout* Layout);

protected:
	MODULE_API void AddLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);
	MODULE_API void RemoveLayoutFromViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);

	MODULE_API virtual void OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);
	MODULE_API virtual void OnRootLayoutRemovedFromViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);
	MODULE_API virtual void OnRootLayoutReleased(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);

	MODULE_API void CreateLayoutWidget(UCommonLocalPlayer* LocalPlayer);
	MODULE_API TSubclassOf<UPrimaryGameLayout> GetLayoutWidgetClass(UCommonLocalPlayer* LocalPlayer);

private:
	ELocalMultiplayerInteractionMode LocalMultiplayerInteractionMode = ELocalMultiplayerInteractionMode::PrimaryOnly;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UPrimaryGameLayout> LayoutClass;

	UPROPERTY(Transient)
	TArray<FRootViewportLayoutInfo> RootViewportLayouts;

private:
	MODULE_API void NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer);
	MODULE_API void NotifyPlayerRemoved(UCommonLocalPlayer* LocalPlayer);
	MODULE_API void NotifyPlayerDestroyed(UCommonLocalPlayer* LocalPlayer);

	friend class UGameUIManagerSubsystem;
};

#undef MODULE_API
