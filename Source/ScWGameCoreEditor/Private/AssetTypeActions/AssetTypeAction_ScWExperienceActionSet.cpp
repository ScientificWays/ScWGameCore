// Scientific Ways

#include "AssetTypeActions/AssetTypeAction_ScWExperienceActionSet.h"

#include "Experience/ScWExperienceActionSet.h"

FText FAssetTypeActions_ScWExperienceActionSet::GetName() const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ExperienceActionSet_Title", "[ScW] Experience Action Set");
}

uint32 FAssetTypeActions_ScWExperienceActionSet::GetCategories() // IAssetTypeActions
{
    return FScWGameCoreEditorModule::GetInputAssetsCategory();
}

FColor FAssetTypeActions_ScWExperienceActionSet::GetTypeColor() const // IAssetTypeActions
{
    return FColor(210, 70, 155);
}

FText FAssetTypeActions_ScWExperienceActionSet::GetAssetDescription(const FAssetData& InAssetData) const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ExperienceActionSet_Description", 
        "Definition of a set of actions to perform as part of entering an experience.");
}

UClass* FAssetTypeActions_ScWExperienceActionSet::GetSupportedClass() const // IAssetTypeActions
{
    return UScWExperienceActionSet::StaticClass();
}
