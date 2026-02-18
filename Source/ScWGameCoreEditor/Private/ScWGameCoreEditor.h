// Scientific Ways

#pragma once

#include "CoreMinimal.h"

#include "Factories/Factory.h"

#include "AssetTypeActions/AssetTypeActions_DataAsset.h"

#include "Modules/ModuleManager.h"

class FScWGameCoreEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override; // IModuleInterface
    virtual void ShutdownModule() override; // IModuleInterface

    /** Provides the asset categories supported by this editor module */
    static EAssetTypeCategories::Type GetInputAssetsCategory() { return InputAssetsCategory; }
private:

    /** All asset categories managed by this editor module */
    static EAssetTypeCategories::Type InputAssetsCategory;

    /** All asset type actions registered by this module */
    TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

    void RegisterAssetTypeActions(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
    {
        AssetTools.RegisterAssetTypeActions(Action);
        CreatedAssetTypeActions.Add(Action);
    }
};
