// Scientific Ways

#pragma once

#include "Blueprint/UserWidgetPool.h"

#include "GameSettingDetailView.generated.h"

#define MODULE_API GAMESETTINGS_API

class UCommonRichTextBlock;
class UCommonTextBlock;
class UGameSetting;
class UGameSettingDetailExtension;
class UGameSettingVisualData;
class UObject;
class UVerticalBox;
struct FStreamableHandle;

/**
 * 
 */
UCLASS(MinimalAPI, Abstract)
class UGameSettingDetailView : public UUserWidget
{
	GENERATED_BODY()
public:
	MODULE_API UGameSettingDetailView(const FObjectInitializer& InObjectInitializer);

	MODULE_API void FillSettingDetails(UGameSetting* InSetting);

	//UVisual interface
	MODULE_API virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

protected:
	MODULE_API virtual void NativeConstruct() override;
	MODULE_API virtual void NativeOnInitialized() override;

	MODULE_API void CreateDetailsExtension(UGameSetting* InSetting, TSubclassOf<UGameSettingDetailExtension> ExtensionClass);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UGameSettingVisualData> VisualData;

	UPROPERTY(Transient)
	FUserWidgetPool ExtensionWidgetPool;

	UPROPERTY(Transient)
	TObjectPtr<UGameSetting> CurrentSetting;

	TSharedPtr<FStreamableHandle> StreamingHandle;

private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonTextBlock> Text_SettingName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonRichTextBlock> RichText_Description;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonRichTextBlock> RichText_DynamicDetails;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonRichTextBlock> RichText_WarningDetails;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonRichTextBlock> RichText_DisabledDetails;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UVerticalBox> Box_DetailsExtension;
};

#undef MODULE_API
