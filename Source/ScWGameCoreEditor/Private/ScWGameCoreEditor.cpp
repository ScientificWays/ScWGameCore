// Scientific Ways

#include "ScWGameCoreEditor.h"

#include "Customization/ScWGameFeatureListCustomization.h"

#include "AssetTypeActions/AssetTypeAction_ScWExperience.h"
#include "AssetTypeActions/AssetTypeAction_ScWExperienceActionSet.h"
#include "AssetTypeActions/AssetTypeAction_ScWExperienceDescription.h"

#include "AssetTypeActions/AssetTypeAction_ScWPawnData.h"
#include "AssetTypeActions/AssetTypeAction_ScWAbilitySet.h"
#include "AssetTypeActions/AssetTypeAction_ScWInputConfig.h"

#define LOCTEXT_NAMESPACE "FScWGameCoreEditorModule"

IMPLEMENT_MODULE(FScWGameCoreEditorModule, ScWGameCoreEditor)

EAssetTypeCategories::Type FScWGameCoreEditorModule::InputAssetsCategory;

void FScWGameCoreEditorModule::StartupModule() // IModuleInterface
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("ScWExperience", FOnGetDetailCustomizationInstance::CreateStatic(&FScWGameFeatureListCustomization::MakeInstance));
	
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	InputAssetsCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("ScWGameCore")), LOCTEXT("ScientificWays_GameCoreCategory", "[ScW] Game Core"));
	{
		RegisterAssetTypeActions(AssetTools, MakeShared<FAssetTypeActions_ScWExperience>());
		RegisterAssetTypeActions(AssetTools, MakeShared<FAssetTypeActions_ScWExperienceActionSet>());
		RegisterAssetTypeActions(AssetTools, MakeShared<FAssetTypeActions_ScWExperienceDescription>());

		RegisterAssetTypeActions(AssetTools, MakeShared<FAssetTypeActions_ScWPawnData>());
		RegisterAssetTypeActions(AssetTools, MakeShared<FAssetTypeActions_ScWAbilitySet>());
		RegisterAssetTypeActions(AssetTools, MakeShared<FAssetTypeActions_ScWInputConfig>());
	}
}

void FScWGameCoreEditorModule::ShutdownModule() // IModuleInterface
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout("ScWExperience");
	}
	if (const FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools"))
	{
		for (TSharedPtr<IAssetTypeActions>& AssetAction : CreatedAssetTypeActions)
		{
			AssetToolsModule->Get().UnregisterAssetTypeActions(AssetAction.ToSharedRef());
		}
	}
	CreatedAssetTypeActions.Empty();
}

#undef LOCTEXT_NAMESPACE
   