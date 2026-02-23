// Scientific Ways

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "CommonInputTypeEnum.h"
#include "UObject/SoftObjectPtr.h"

#include "CommonUIExtensions.generated.h"

#define MODULE_API COMMONGAME_API

enum class ECommonInputType : uint8;
template <typename T> class TSubclassOf;

class APlayerController;
class UCommonActivatableWidget;
class ULocalPlayer;
class UObject;
class UUserWidget;
struct FFrame;
struct FGameplayTag;

//DECLARE_DYNAMIC_DELEGATE_OneParam(FCommonUIInitInstanceSignature, UCommonActivatableWidget*, InWidget);

UCLASS(MinimalAPI)
class UCommonUIExtensions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(Category = "Global UI Extensions", BlueprintCallable, meta = (CallableWithoutWorldContext, DefaultToSelf = "InPlayerContext"))
	static MODULE_API const ULocalPlayer* GetLocalPlayerFromContext(const UObject* InPlayerContext);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext, DefaultToSelf = "InPlayerContext"))
	static MODULE_API ECommonInputType GetOwningPlayerInputType(const UObject* InPlayerContext);

	UFUNCTION(Category = "Global UI Extensions", BlueprintCallable, meta = (CallableWithoutWorldContext, DefaultToSelf = "InPlayerContext", ExpandEnumAsExecs = "ReturnValue"))
	static MODULE_API ECommonInputType SwitchOnPlayerInputType(const UObject* InPlayerContext);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext, DefaultToSelf = "InPlayerContext"))
	static MODULE_API bool IsOwningPlayerUsingTouch(const UObject* InPlayerContext);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext, DefaultToSelf = "InPlayerContext"))
	static MODULE_API bool IsOwningPlayerUsingGamepad(const UObject* InPlayerContext);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext, DeterminesOutputType = InWidgetClass))
	static MODULE_API UCommonActivatableWidget* PushContentToLayer_ForPlayer(const ULocalPlayer* InLocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag InLayerName, UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UCommonActivatableWidget> InWidgetClass);
	
	//UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext, DeterminesOutputType = InWidgetClass))
	//static MODULE_API UCommonActivatableWidget* PushContentToLayerAndInit_ForPlayer(const ULocalPlayer* InLocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag InLayerName, UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UCommonActivatableWidget> InWidgetClass, FCommonUIInitInstanceSignature InInitInstanceFunc);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext))
	static MODULE_API void PushStreamedContentToLayer_ForPlayer(const ULocalPlayer* InLocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag InLayerName, UPARAM(meta = (AllowAbstract = false)) TSoftClassPtr<UCommonActivatableWidget> InWidgetClass);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext, DefaultToSelf = "InActivatableWidget"))
	static MODULE_API void PopContentFromLayer(UCommonActivatableWidget* InActivatableWidget);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext))
	static MODULE_API ULocalPlayer* GetLocalPlayerFromController(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext))
	static MODULE_API FName SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason);

	static MODULE_API FName SuspendInputForPlayer(ULocalPlayer* InLocalPlayer, FName SuspendReason);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions", meta = (CallableWithoutWorldContext))
	static MODULE_API void ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken);

	static MODULE_API void ResumeInputForPlayer(ULocalPlayer* InLocalPlayer, FName SuspendToken);

private:
	static MODULE_API int32 InputSuspensions;
};

#undef MODULE_API
