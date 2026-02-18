// Scientific Ways

#pragma once

#include "CommonUserWidget.h"
#include "Containers/Ticker.h"
#include "GameSettingFilterState.h"
#include "GameplayTagContainer.h"
#include "Misc/ExpressionParserTypesFwd.h"

#include "GameSettingPanel.generated.h"

#define MODULE_API GAMESETTINGS_API

class UGameSetting;
class UGameSettingDetailView;
class UGameSettingListView;
class UGameSettingRegistry;
class UObject;
struct FFocusEvent;
struct FGeometry;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusedSettingChanged, UGameSetting*)

UCLASS(MinimalAPI, Abstract)
class UGameSettingPanel : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	MODULE_API UGameSettingPanel();
	MODULE_API virtual void NativeOnInitialized() override;
	MODULE_API virtual void NativeConstruct() override;
	MODULE_API virtual void NativeDestruct() override;

	// Focus transitioning to subwidgets for the gamepad
	MODULE_API virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	/**  */
	MODULE_API void SetRegistry(UGameSettingRegistry* InRegistry);

	/** Sets the filter for this panel, restricting which settings are available currently. */
	MODULE_API void SetFilterState(const FGameSettingFilterState& InFilterState, bool bClearNavigationStack = true);

	/** Gets the currently visible and available settings based on the filter state. */
	TArray<UGameSetting*> GetVisibleSettings() const { return VisibleSettings; }

	/** Can we pop the current navigation stack */
	MODULE_API bool CanPopNavigationStack() const;

	/** Pop the navigation stack */
	MODULE_API void PopNavigationStack();

	/**
	 * Gets the set of settings that are potentially available on this screen.
	 * MAY CONTAIN INVISIBLE SETTINGS.
	 * DOES NOT INCLUDED NESTED PAGES.
	 */
	MODULE_API TArray<UGameSetting*> GetSettingsWeCanResetToDefault() const;

	MODULE_API void SelectSetting(const FName& SettingDevName);
	MODULE_API UGameSetting* GetSelectedSetting() const;

	MODULE_API void RefreshSettingsList();

	FOnFocusedSettingChanged OnFocusedSettingChanged;

protected:
	MODULE_API void RegisterRegistryEvents();
	MODULE_API void UnregisterRegistryEvents();
	
	MODULE_API void HandleSettingItemHoveredChanged(UObject* Item, bool bHovered);
	MODULE_API void HandleSettingItemSelectionChanged(UObject* Item);
	MODULE_API void FillSettingDetails(UGameSetting* InSetting);
	MODULE_API void HandleSettingNamedAction(UGameSetting* Setting, FGameplayTag GameSettings_Action_Tag);
	MODULE_API void HandleSettingNavigation(UGameSetting* Setting);
	MODULE_API void HandleSettingEditConditionsChanged(UGameSetting* Setting);

private:

	UPROPERTY(Transient)
	TObjectPtr<UGameSettingRegistry> Registry;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UGameSetting>> VisibleSettings;

	UPROPERTY(Transient)
	TObjectPtr<UGameSetting> LastHoveredOrSelectedSetting;

	UPROPERTY(Transient)
	FGameSettingFilterState FilterState;

	UPROPERTY(Transient)
	TArray<FGameSettingFilterState> FilterNavigationStack;

	FName DesiredSelectionPostRefresh;

	bool bAdjustListViewPostRefresh = true;

private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGameSettingListView> ListView_Settings;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGameSettingDetailView> Details_Settings;

private:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExecuteNamedActionBP, UGameSetting*, Setting, FGameplayTag, Action);
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Execute Named Action"))
	FOnExecuteNamedActionBP BP_OnExecuteNamedAction;

private:
	FTSTicker::FDelegateHandle RefreshHandle;
};

#undef MODULE_API
