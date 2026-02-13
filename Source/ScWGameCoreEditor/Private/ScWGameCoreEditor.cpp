#include "ScWGameCoreEditor.h"
#include "Customization/ScWGameFeatureListCustomization.h"

#define LOCTEXT_NAMESPACE "FScWGameCoreEditorModule"

void FScWGameCoreEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("ScWExperience", FOnGetDetailCustomizationInstance::CreateStatic(&FScWGameFeatureListCustomization::MakeInstance));
}

void FScWGameCoreEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout("ScWExperience");
	}   
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FScWGameCoreEditorModule, ScWGameCoreEditor)