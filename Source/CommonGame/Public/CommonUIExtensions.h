// Scientific Ways

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
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

UCLASS(MinimalAPI)
class UCommonUIExtensions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UCommonUIExtensions() { }
	
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", meta = (WorldContext = "WidgetContextObject"))
	static MODULE_API ECommonInputType GetOwningPlayerInputType(const UUserWidget* WidgetContextObject);
	
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", meta = (WorldContext = "WidgetContextObject"))
	static MODULE_API bool IsOwningPlayerUsingTouch(const UUserWidget* WidgetContextObject);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", meta = (WorldContext = "WidgetContextObject"))
	static MODULE_API bool IsOwningPlayerUsingGamepad(const UUserWidget* WidgetContextObject);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static MODULE_API UCommonActivatableWidget* PushContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UCommonActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static MODULE_API void PushStreamedContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UPARAM(meta = (AllowAbstract = false)) TSoftClassPtr<UCommonActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static MODULE_API void PopContentFromLayer(UCommonActivatableWidget* ActivatableWidget);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static MODULE_API ULocalPlayer* GetLocalPlayerFromController(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static MODULE_API FName SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason);

	static MODULE_API FName SuspendInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendReason);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static MODULE_API void ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken);

	static MODULE_API void ResumeInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendToken);

private:
	static MODULE_API int32 InputSuspensions;
};

#undef MODULE_API
