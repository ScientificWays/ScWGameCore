// Scientific Ways

#pragma once

#include "ScWGameCoreEditor.h"

class FAssetTypeActions_ScWExperienceActionSet final : public FAssetTypeActions_DataAsset
{
public:
    virtual FText GetName() const override; // IAssetTypeActions
    virtual uint32 GetCategories() override; // IAssetTypeActions
    virtual FColor GetTypeColor() const override; // IAssetTypeActions
    virtual FText GetAssetDescription(const FAssetData& InAssetData) const override; // IAssetTypeActions
    virtual UClass* GetSupportedClass() const override; // IAssetTypeActions
};