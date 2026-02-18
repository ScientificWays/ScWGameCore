// Scientific Ways

#include "AssetTypeActions/AssetTypeAction_ScWAbilitySet.h"

#include "AbilitySystem/ScWAbilitySet.h"

FText FAssetTypeActions_ScWAbilitySet::GetName() const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_AbilitySet_Title", "[ScW] Ability Set");
}

uint32 FAssetTypeActions_ScWAbilitySet::GetCategories() // IAssetTypeActions
{
    return FScWGameCoreEditorModule::GetInputAssetsCategory();
}

FColor FAssetTypeActions_ScWAbilitySet::GetTypeColor() const // IAssetTypeActions
{
    return FColor(240, 200, 60);
}

FText FAssetTypeActions_ScWAbilitySet::GetAssetDescription(const FAssetData& InAssetData) const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_AbilitySet_Description", 
        "Non-mutable data asset used to grant gameplay abilities, effects and tags.");
}

UClass* FAssetTypeActions_ScWAbilitySet::GetSupportedClass() const // IAssetTypeActions
{
    return UScWAbilitySet::StaticClass();
}
