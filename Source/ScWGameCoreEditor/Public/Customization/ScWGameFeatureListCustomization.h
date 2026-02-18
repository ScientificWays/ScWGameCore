// Scientific Ways

#pragma once

#include "CoreMinimal.h"

#include "IDetailCustomization.h"

class SCWGAMECOREEDITOR_API FScWGameFeatureListCustomization final : public IDetailCustomization
{
private:
	TArray<TSharedPtr<FString>> GameFeatureOptions;
    TArray<TSharedPtr<FString>> GameFeatureStateOptions;
	
protected:
	void PopulateGameFeatureList();
	void OnGameFeatureChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo, TSharedPtr<IPropertyHandle> KeyHandle);
	void OnGameFeatureStateChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);
	
public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	
	// Static accessor
	static TSharedRef<IDetailCustomization> MakeInstance();
};
