// Scientific Ways

#pragma once

#include "LoadingProcessInterface.h"
#include "UObject/Object.h"

#include "LoadingProcessTask.generated.h"

#define MODULE_API COMMONLOADINGSCREEN_API

struct FFrame;

UCLASS(MinimalAPI, BlueprintType)
class ULoadingProcessTask : public UObject, public ILoadingProcessInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static MODULE_API ULoadingProcessTask* CreateLoadingScreenProcessTask(UObject* WorldContextObject, const FString& ShowLoadingScreenReason);

public:
	ULoadingProcessTask() { }

	UFUNCTION(BlueprintCallable)
	MODULE_API void Unregister();

	UFUNCTION(BlueprintCallable)
	MODULE_API void SetShowLoadingScreenReason(const FString& InReason);

	MODULE_API virtual bool ShouldShowLoadingScreen(FString& OutReason) const override;
	
	FString Reason;
};

#undef MODULE_API
