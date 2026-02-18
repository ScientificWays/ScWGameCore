// Scientific Ways

#include "AssetTypeActions/AssetTypeAction_ScWExperience.h"

#include "Experience/ScWExperience.h"

FText FAssetTypeActions_ScWExperience::GetName() const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Experience_Title", "[ScW] Experience");
}

uint32 FAssetTypeActions_ScWExperience::GetCategories() // IAssetTypeActions
{
    return FScWGameCoreEditorModule::GetInputAssetsCategory();
}

FColor FAssetTypeActions_ScWExperience::GetTypeColor() const // IAssetTypeActions
{
    return FColor(230, 90, 170);
}

FText FAssetTypeActions_ScWExperience::GetAssetDescription(const FAssetData& InAssetData) const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Experience_Description", 
        "Definition of an experience.");
}

UClass* FAssetTypeActions_ScWExperience::GetSupportedClass() const // IAssetTypeActions
{
    return UScWExperience::StaticClass();
}
