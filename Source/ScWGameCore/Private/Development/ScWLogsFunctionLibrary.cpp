// Scientific Ways

#include "Development/ScWLogsFunctionLibrary.h"

//UE_DISABLE_OPTIMIZATION

#define LOG_BP_TEMPLATE(InCategory, InCategoryString) \
void UScWLogsFunctionLibrary::Log_##InCategory(const UObject* InContext, const FString& InMessage, EBlueprintLogVerbosity InVerbosity, bool bInPrintToLog, bool bInPrintToScreen, const FName InPrintToScreenKey) \
{ \
	if (bInPrintToLog) \
	{ \
		FString LogMessage = FString::Printf(TEXT("%s (%s)"), *InMessage, *GetNameSafe(InContext)); \
		switch (InVerbosity) \
		{ \
			case EBlueprintLogVerbosity::Fatal: \
				UE_LOG(LogScW##InCategory, Fatal, TEXT("%s"), *LogMessage); break; \
			case EBlueprintLogVerbosity::Error: \
				UE_LOG(LogScW##InCategory, Error, TEXT("%s"), *LogMessage); break; \
			case EBlueprintLogVerbosity::Warning: \
				UE_LOG(LogScW##InCategory, Warning, TEXT("%s"), *LogMessage); break; \
			case EBlueprintLogVerbosity::Display: \
				UE_LOG(LogScW##InCategory, Display, TEXT("%s"), *LogMessage); break; \
			case EBlueprintLogVerbosity::Log: \
				UE_LOG(LogScW##InCategory, Log, TEXT("%s"), *LogMessage); break; \
			case EBlueprintLogVerbosity::Verbose: \
				UE_LOG(LogScW##InCategory, Verbose, TEXT("%s"), *LogMessage); break; \
			case EBlueprintLogVerbosity::VeryVerbose: \
				UE_LOG(LogScW##InCategory, VeryVerbose, TEXT("%s"), *LogMessage); break; \
		} \
	} \
	if (bInPrintToScreen) \
	{ \
		FString ScreenMessage = FString::Printf(TEXT("LogScW%s: %s (%s)"), TEXT(InCategoryString), *InMessage, *GetNameSafe(InContext)); \
		switch (InVerbosity) \
		{ \
			case EBlueprintLogVerbosity::Fatal: \
				if (UE_LOG_ACTIVE(LogScW##InCategory, Fatal)) \
					UKismetSystemLibrary::PrintString(InContext, ScreenMessage, true, false, FLinearColor::Red, 600.0f, InPrintToScreenKey); \
				break; \
			case EBlueprintLogVerbosity::Error: \
				if (UE_LOG_ACTIVE(LogScW##InCategory, Error)) \
					UKismetSystemLibrary::PrintString(InContext, ScreenMessage, true, false, FLinearColor::Red, 600.0f, InPrintToScreenKey); \
				break; \
			case EBlueprintLogVerbosity::Warning: \
				if (UE_LOG_ACTIVE(LogScW##InCategory, Warning)) \
					UKismetSystemLibrary::PrintString(InContext, ScreenMessage, true, false, FLinearColor::Yellow, 60.0f, InPrintToScreenKey); \
				break; \
			case EBlueprintLogVerbosity::Display: \
				if (UE_LOG_ACTIVE(LogScW##InCategory, Display)) \
					UKismetSystemLibrary::PrintString(InContext, ScreenMessage, true, false, FLinearColor(0.0f, 1.0f, 1.0f), 5.0f, InPrintToScreenKey); \
				break; \
			case EBlueprintLogVerbosity::Log: \
				if (UE_LOG_ACTIVE(LogScW##InCategory, Log)) \
					UKismetSystemLibrary::PrintString(InContext, ScreenMessage, true, false, FLinearColor(0.0f, 1.0f, 1.0f), 5.0f, InPrintToScreenKey); \
				break; \
			case EBlueprintLogVerbosity::Verbose: \
				if (UE_LOG_ACTIVE(LogScW##InCategory, Verbose)) \
					UKismetSystemLibrary::PrintString(InContext, ScreenMessage, true, false, FLinearColor::White, 2.0f, InPrintToScreenKey); \
				break; \
			case EBlueprintLogVerbosity::VeryVerbose: \
				if (UE_LOG_ACTIVE(LogScW##InCategory, VeryVerbose)) \
					UKismetSystemLibrary::PrintString(InContext, ScreenMessage, true, false, FLinearColor::White, 1.0f, InPrintToScreenKey); \
				break; \
		} \
	} \
}

LOG_BP_TEMPLATE(AbilitySystem, "AbilitySystem")
LOG_BP_TEMPLATE(GameMode, "GameMode")
LOG_BP_TEMPLATE(World, "World")

//UE_ENABLE_OPTIMIZATION
