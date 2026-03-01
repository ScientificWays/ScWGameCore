// Scientific Ways

#pragma once

#include "Components/ListView.h"

#include "GameSettingListView.generated.h"

#define MODULE_API GAMESETTINGS_API

class STableViewBase;

class UGameSettingCollection;
class ULocalPlayer;
class UGameSettingVisualData;

/**
 * List of game settings.  Every entry widget needs to extend from GameSettingListEntryBase.
 */
UCLASS(MinimalAPI, meta = (EntryClass = GameSettingListEntryBase))
class UGameSettingListView : public UListView
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingListView(const FObjectInitializer& InObjectInitializer);

	MODULE_API void AddNameOverride(const FName& DevName, const FText& OverrideName);

#if WITH_EDITOR
	MODULE_API virtual void ValidateCompiledDefaults(IWidgetCompilerLog& InCompileLog) const override;
#endif

protected:
	MODULE_API virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	MODULE_API virtual bool OnIsSelectableOrNavigableInternal(UObject* SelectedItem) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UGameSettingVisualData> VisualData;

private:
	TMap<FName, FText> NameOverrides;
};

#undef MODULE_API
