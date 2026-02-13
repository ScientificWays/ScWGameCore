#include "Customization/ScWGameFeatureListCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "GameFeaturesSubsystem.h"
#include "IDetailChildrenBuilder.h"
#include "PropertyCustomizationHelpers.h"
#include "Experience/ScWExperience.h"
#include "Engine/AssetManager.h"

void FScWGameFeatureListCustomization::PopulateGameFeatureList()
{
	// Clear cached game features
	GameFeatureOptions.Empty();
    
	// Extract all registered game features
	TArray<FPrimaryAssetId> AssetIds;
	UAssetManager::Get().GetPrimaryAssetIdList(FName("GameFeatureData"), AssetIds);

	// Cache game feature list
	for (const FPrimaryAssetId& AssetId : AssetIds)
	{
		const auto& AssetName = AssetId.ToString();
		GameFeatureOptions.Add(MakeShareable(new FString(AssetName)));
	}
}

void FScWGameFeatureListCustomization::OnGameFeatureChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo, TSharedPtr<IPropertyHandle> KeyHandle)
{
	if (NewValue.IsValid())
	{
		KeyHandle->SetValue(*NewValue);
	}
}

void FScWGameFeatureListCustomization::OnGameFeatureStateChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)
{
}

void FScWGameFeatureListCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Refresh actual game feature list
	// PopulateGameFeatureList();
	//
	// // Find property
	// IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Gameplay");
	// TSharedPtr<IPropertyHandle> PropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UScWExperience, ListOfGameFeatures));
}

TSharedRef<IDetailCustomization> FScWGameFeatureListCustomization::MakeInstance()
{
	return MakeShareable(new FScWGameFeatureListCustomization);
}
