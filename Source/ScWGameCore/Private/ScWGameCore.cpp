// Scientific Ways

#include "ScWGameCore.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FScWGameCoreModule"

DEFINE_LOG_CATEGORY(LogScWGameCore);

IMPLEMENT_MODULE(FScWGameCoreModule, ScWGameCore)

void FScWGameCoreModule::StartupModule() // IModuleInterface
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FScWGameCoreModule::ShutdownModule() // IModuleInterface
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
