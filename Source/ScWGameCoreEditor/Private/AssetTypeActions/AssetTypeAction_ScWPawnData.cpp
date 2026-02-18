// Scientific Ways

#include "AssetTypeActions/AssetTypeAction_ScWPawnData.h"

#include "Character/ScWPawnData.h"

FText FAssetTypeActions_ScWPawnData::GetName() const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_PawnData_Title", "[ScW] Pawn Data");
}

uint32 FAssetTypeActions_ScWPawnData::GetCategories() // IAssetTypeActions
{
    return FScWGameCoreEditorModule::GetInputAssetsCategory();
}

FColor FAssetTypeActions_ScWPawnData::GetTypeColor() const // IAssetTypeActions
{
    return FColor(120, 80, 220);
}

FText FAssetTypeActions_ScWPawnData::GetAssetDescription(const FAssetData& InAssetData) const // IAssetTypeActions
{
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_PawnData_Description", 
        "Non-mutable data asset that contains properties used to define a pawn.");
}

UClass* FAssetTypeActions_ScWPawnData::GetSupportedClass() const // IAssetTypeActions
{
    return UScWPawnData::StaticClass();
}
