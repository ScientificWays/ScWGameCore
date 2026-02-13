// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWInputFunctionLibrary.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Gameplay Function Library"))
class UScWInputFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

//~ Begin Input
public:

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (AutoCreateRefTerm = "InOptions", KeyWords = "AddInputMappingContextTo"))
	static MODULE_API bool AddEnhancedInputMappingContextTo(APlayerController* InPlayerController, const UInputMappingContext* InMappingContext, int32 InPriority, const FModifyContextOptions& InOptions = FModifyContextOptions());

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (AutoCreateRefTerm = "InOptions", KeyWords = "RemoveInputMappingContextFrom"))
	static MODULE_API bool RemoveEnhancedInputMappingContextFrom(APlayerController* InPlayerController, const UInputMappingContext* InMappingContext, const FModifyContextOptions& InOptions = FModifyContextOptions());
	
	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, BlueprintPure)
	static MODULE_API bool GetActionMappedKeyDisplayName(APlayerController* InPlayerController, const UInputAction* InInputAction, const bool bInLongDisplayName, FText& OutDisplayName);
//~ End Input
};

#undef MODULE_API
