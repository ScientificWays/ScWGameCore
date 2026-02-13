// Scientific Ways

#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "CommonUserWidget.h"

#include "GameSettingListEntry.generated.h"

#define MODULE_API GAMESETTINGS_API

class FGameSettingEditableState;
enum class EGameSettingChangeReason : uint8;

class UAnalogSlider;
class UCommonButtonBase;
class UCommonTextBlock;
class UGameSetting;
class UGameSettingAction;
class UGameSettingCollectionPage;
class UGameSettingRotator;
class UGameSettingValueDiscrete;
class UGameSettingValueScalar;
class UObject;
class UPanelWidget;
class UUserWidget;
class UWidget;
struct FFocusEvent;
struct FFrame;
struct FGeometry;

//////////////////////////////////////////////////////////////////////////
// UAthenaChallengeListEntry
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, Abstract, NotBlueprintable, meta = (Category = "Settings", DisableNativeTick))
class UGameSettingListEntryBase : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	MODULE_API virtual void SetSetting(UGameSetting* InSetting);
	MODULE_API virtual void SetDisplayNameOverride(const FText& OverrideName);

protected:
	MODULE_API virtual void NativeOnEntryReleased() override;
	MODULE_API virtual void OnSettingChanged();
	MODULE_API virtual void HandleEditConditionChanged(UGameSetting* InSetting);
	MODULE_API virtual void RefreshEditableState(const FGameSettingEditableState& InEditableState);
	
protected:
	// Focus transitioning to subwidgets for the gamepad
	MODULE_API virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API UWidget* GetPrimaryGamepadFocusWidget();

protected:
	bool bSuspendChangeUpdates = false;

	UPROPERTY()
	TObjectPtr<UGameSetting> Setting;

	FText DisplayNameOverride = FText::GetEmpty();

private:
	void HandleSettingChanged(UGameSetting* InSetting, EGameSettingChangeReason Reason);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UUserWidget> Background;
};


//////////////////////////////////////////////////////////////////////////
// UGameSettingListEntry_Setting
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (Category = "Settings", DisableNativeTick))
class UGameSettingListEntry_Setting : public UGameSettingListEntryBase
{
	GENERATED_BODY()

public:
	MODULE_API virtual void SetSetting(UGameSetting* InSetting) override;
	
private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonTextBlock> Text_SettingName;
};


//////////////////////////////////////////////////////////////////////////
// UGameSettingListEntrySetting_Discrete
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (Category = "Settings", DisableNativeTick))
class UGameSettingListEntrySetting_Discrete : public UGameSettingListEntry_Setting
{
	GENERATED_BODY()

public:
	MODULE_API virtual void SetSetting(UGameSetting* InSetting) override;
	
protected:
	MODULE_API virtual void NativeOnInitialized() override;
	MODULE_API virtual void NativeOnEntryReleased() override;

	MODULE_API void HandleOptionDecrease();
	MODULE_API void HandleOptionIncrease();
	MODULE_API void HandleRotatorChangedValue(int32 Value, bool bUserInitiated);

	MODULE_API void Refresh();
	MODULE_API virtual void OnSettingChanged() override;
	MODULE_API virtual void HandleEditConditionChanged(UGameSetting* InSetting) override;
	MODULE_API virtual void RefreshEditableState(const FGameSettingEditableState& InEditableState) override;

protected:
	UPROPERTY()
	TObjectPtr<UGameSettingValueDiscrete> DiscreteSetting;

private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPanelWidget> Panel_Value;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGameSettingRotator> Rotator_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Decrease;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Increase;
};

//////////////////////////////////////////////////////////////////////////
// UGameSettingListEntrySetting_Scalar
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (Category = "Settings", DisableNativeTick))
class UGameSettingListEntrySetting_Scalar : public UGameSettingListEntry_Setting
{
	GENERATED_BODY()

public:
	MODULE_API virtual void SetSetting(UGameSetting* InSetting) override;

protected:
	MODULE_API void Refresh();
	MODULE_API virtual void NativeOnInitialized() override;
	MODULE_API virtual void NativeOnEntryReleased() override;
	MODULE_API virtual void OnSettingChanged() override;

	UFUNCTION()
	MODULE_API void HandleSliderValueChanged(float Value);
	UFUNCTION()
	MODULE_API void HandleSliderCaptureEnded();

	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void OnValueChanged(float Value);

	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void OnDefaultValueChanged(float DefaultValue);

	MODULE_API virtual void RefreshEditableState(const FGameSettingEditableState& InEditableState) override;

protected:
	UPROPERTY()
	TObjectPtr<UGameSettingValueScalar> ScalarSetting;

private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPanelWidget> Panel_Value;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UAnalogSlider> Slider_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonTextBlock> Text_SettingValue;
};


//////////////////////////////////////////////////////////////////////////
// UGameSettingListEntrySetting_Action
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (Category = "Settings", DisableNativeTick))
class UGameSettingListEntrySetting_Action : public UGameSettingListEntry_Setting
{
	GENERATED_BODY()

public:
	MODULE_API virtual void SetSetting(UGameSetting* InSetting) override;

protected:
	MODULE_API virtual void NativeOnInitialized() override;
	MODULE_API virtual void NativeOnEntryReleased() override;
	MODULE_API virtual void RefreshEditableState(const FGameSettingEditableState& InEditableState) override;

	MODULE_API void HandleActionButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void OnSettingAssigned(const FText& ActionText);

protected:
	UPROPERTY()
	TObjectPtr<UGameSettingAction> ActionSetting;

private:	// Bound Widgets

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Action;
};

//////////////////////////////////////////////////////////////////////////
// UGameSettingListEntrySetting_Navigation
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (Category = "Settings", DisableNativeTick))
class UGameSettingListEntrySetting_Navigation : public UGameSettingListEntry_Setting
{
	GENERATED_BODY()

public:
	MODULE_API virtual void SetSetting(UGameSetting* InSetting) override;

protected:
	MODULE_API virtual void NativeOnInitialized() override;
	MODULE_API virtual void NativeOnEntryReleased() override;
	MODULE_API virtual void RefreshEditableState(const FGameSettingEditableState& InEditableState) override;

	MODULE_API void HandleNavigationButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void OnSettingAssigned(const FText& ActionText);

protected:
	UPROPERTY()
	TObjectPtr<UGameSettingCollectionPage> CollectionSetting;

private:	// Bound Widgets

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Navigate;
};

#undef MODULE_API
