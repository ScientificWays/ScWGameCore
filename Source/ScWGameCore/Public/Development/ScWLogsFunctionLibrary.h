// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Development/ScWLogs.h"

#include "ScWLogsFunctionLibrary.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI)
class UScWLogsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(Category = "Development", BlueprintCallable, meta = (CallableWithoutWorldContext, DefaultToSelf = "InContext", AutoCreateRefTerm = "InMessage", AdvancedDisplay = "3", DevelopmentOnly, DisplayName = "[ScW] Log Ability System"))
	static MODULE_API void Log_AbilitySystem(const UObject* InContext, const FString& InMessage, EBlueprintLogVerbosity InVerbosity = EBlueprintLogVerbosity::Log, bool bInPrintToLog = true, bool bInPrintToScreen = true, const FName InPrintToScreenKey = NAME_None);

	UFUNCTION(Category = "Development", BlueprintCallable, meta = (CallableWithoutWorldContext, DefaultToSelf = "InContext", AutoCreateRefTerm = "InMessage", AdvancedDisplay = "3", DevelopmentOnly, DisplayName = "[ScW] Log Game Mode"))
	static MODULE_API void Log_GameMode(const UObject* InContext, const FString& InMessage, EBlueprintLogVerbosity InVerbosity = EBlueprintLogVerbosity::Log, bool bInPrintToLog = true, bool bInPrintToScreen = true, const FName InPrintToScreenKey = NAME_None);

	UFUNCTION(Category = "Development", BlueprintCallable, meta = (CallableWithoutWorldContext, DefaultToSelf = "InContext", AutoCreateRefTerm = "InMessage", AdvancedDisplay = "3", DevelopmentOnly, DisplayName = "[ScW] Log World"))
	static MODULE_API void Log_World(const UObject* InContext, const FString& InMessage, EBlueprintLogVerbosity InVerbosity = EBlueprintLogVerbosity::Log, bool bInPrintToLog = true, bool bInPrintToScreen = true, const FName InPrintToScreenKey = NAME_None);
};

#undef MODULE_API
