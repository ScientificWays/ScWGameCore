// Scientific Ways

#include "AssetTypeActions/AssetTypeAction_ScWExperienceDescription.h"

#include "Experience/ScWExperienceDescription.h"

FText FAssetTypeActions_ScWExperienceDescription::GetName() const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ExperienceDescription_Title", "[ScW] Experience Description");
}

uint32 FAssetTypeActions_ScWExperienceDescription::GetCategories() // IAssetTypeActions
{
    return FScWGameCoreEditorModule::GetInputAssetsCategory();
}

FColor FAssetTypeActions_ScWExperienceDescription::GetTypeColor() const // IAssetTypeActions
{
    return FColor(245, 120, 185);
}

FText FAssetTypeActions_ScWExperienceDescription::GetAssetDescription(const FAssetData& InAssetData) const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ExperienceDescription_Description", 
        "Description of settings used to display experiences in the UI and start a new session.");
}

UClass* FAssetTypeActions_ScWExperienceDescription::GetSupportedClass() const // IAssetTypeActions
{
    return UScWExperienceDescription::StaticClass();
}
