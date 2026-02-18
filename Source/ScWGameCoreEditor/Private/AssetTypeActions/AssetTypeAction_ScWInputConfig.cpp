// Scientific Ways

#include "AssetTypeActions/AssetTypeAction_ScWInputConfig.h"

#include "Input/ScWInputConfig.h"

FText FAssetTypeActions_ScWInputConfig::GetName() const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_InputConfig_Title", "[ScW] Input Config");
}

uint32 FAssetTypeActions_ScWInputConfig::GetCategories() // IAssetTypeActions
{
    return FScWGameCoreEditorModule::GetInputAssetsCategory();
}

FColor FAssetTypeActions_ScWInputConfig::GetTypeColor() const // IAssetTypeActions
{
    return FColor(70, 200, 120);
}

FText FAssetTypeActions_ScWInputConfig::GetAssetDescription(const FAssetData& InAssetData) const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_InputConfig_Description", 
        "Non-mutable data asset that contains input configuration properties.");
}

UClass* FAssetTypeActions_ScWInputConfig::GetSupportedClass() const // IAssetTypeActions
{
    return UScWInputConfig::StaticClass();
}
