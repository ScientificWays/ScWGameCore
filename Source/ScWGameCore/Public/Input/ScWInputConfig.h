// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "ScWInputConfig.generated.h"

#define MODULE_API SCWGAMECORE_API

class UInputAction;
class UObject;
struct FFrame;

/**
 *	Struct used to map a input action to a gameplay input tag.
 */
USTRUCT(BlueprintType)
struct FScWInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 *	Non-mutable data asset that contains input configuration properties.
 */
UCLASS(MinimalAPI, BlueprintType, Const, meta = (DisplayName = "[ScW] Input Config"))
class UScWInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UScWInputConfig(const FObjectInitializer& InObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Input Config")
	MODULE_API const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bInLogIfNotFound = true) const;

	UFUNCTION(BlueprintCallable, Category = "Input Config")
	MODULE_API const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bInLogIfNotFound = true) const;

public:
	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FScWInputAction> NativeInputActions;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and are automatically bound to abilities with matching input tags.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FScWInputAction> AbilityInputActions;
};

#undef MODULE_API
