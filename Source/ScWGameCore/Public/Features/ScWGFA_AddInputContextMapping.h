// Scientific Ways

#pragma once

#include "ScWGFA_WorldActionBase.h"
#include "UObject/SoftObjectPtr.h"
#include "ScWGFA_AddInputContextMapping.generated.h"

#define MODULE_API SCWGAMECORE_API

class AActor;
class UInputMappingContext;
class UPlayer;
class APlayerController;
struct FComponentRequestHandle;

/**
 *	Pairs an Enhanced Input mapping context with its priority and registration settings.
 */
USTRUCT(BlueprintType)
struct FInputMappingContextAndPriority
{
	GENERATED_BODY()

	UPROPERTY(Category = "Input", EditAnywhere, meta = (AssetBundles = "Client, Server"))
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	// Higher priority input mappings will be prioritized over mappings with a lower priority.
	UPROPERTY(Category = "Input", EditAnywhere)
	int32 Priority = 0;

	/** If true, then this mapping context will be registered with the settings when this game feature action is registered. */
	UPROPERTY(Category = "Input", EditAnywhere)
	bool bRegisterWithSettings = true;
};

/**
 * Adds InputMappingContext to local players' EnhancedInput system. 
 * Expects that local players are set up to use the EnhancedInput system.
 */
UCLASS(MinimalAPI, meta = (DisplayName = "Add Input Mapping"))
class UScWGFA_AddInputContextMapping final : public UScWGFA_WorldActionBase
{
	GENERATED_BODY()

public:
	//~UGameFeatureAction interface
	virtual void OnGameFeatureRegistering() override;
	virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
	virtual void OnGameFeatureUnregistering() override;
	//~End of UGameFeatureAction interface

	//~UObject interface
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
	//~End of UObject interface

	UPROPERTY(Category = "Input", EditAnywhere)
	TArray<FInputMappingContextAndPriority> InputMappings;

private:
	struct FPerContextData
	{
		TArray<TSharedPtr<FComponentRequestHandle>> ExtensionRequestHandles;
		TArray<TWeakObjectPtr<APlayerController>> ControllersAddedTo;
	};

	TMap<FGameFeatureStateChangeContext, FPerContextData> ContextData;
	
	/** Delegate for when the game instance is changed to register IMC's */
	FDelegateHandle RegisterInputContextMappingsForGameInstanceHandle;

	/** Registers owned Input Mapping Contexts to the Input Registry Subsystem. Also binds onto the start of GameInstances and the adding/removal of Local Players. */
	void RegisterInputMappingContexts();
	
	/** Registers owned Input Mapping Contexts to the Input Registry Subsystem for a specified GameInstance. This also gets called by a GameInstance Start. */
	void RegisterInputContextMappingsForGameInstance(UGameInstance* GameInstance);

	/** Registers owned Input Mapping Contexts to the Input Registry Subsystem for a specified Local Player. This also gets called when a Local Player is added. */
	void RegisterInputMappingContextsForLocalPlayer(ULocalPlayer* LocalPlayer);

	/** Unregisters owned Input Mapping Contexts from the Input Registry Subsystem. Also unbinds from the start of GameInstances and the adding/removal of Local Players. */
	void UnregisterInputMappingContexts();

	/** Unregisters owned Input Mapping Contexts from the Input Registry Subsystem for a specified GameInstance. */
	void UnregisterInputContextMappingsForGameInstance(UGameInstance* GameInstance);

	/** Unregisters owned Input Mapping Contexts from the Input Registry Subsystem for a specified Local Player. This also gets called when a Local Player is removed. */
	void UnregisterInputMappingContextsForLocalPlayer(ULocalPlayer* LocalPlayer);

	//~UScWGFA_WorldActionBase interface
	virtual void AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext) override;
	//~End of UScWGFA_WorldActionBase interface

	void Reset(FPerContextData& ActiveData);
	void HandleControllerExtension(AActor* Actor, FName EventName, FGameFeatureStateChangeContext ChangeContext);
	void AddInputMappingForPlayer(UPlayer* Player, FPerContextData& ActiveData);
	void RemoveInputMapping(APlayerController* PlayerController, FPerContextData& ActiveData);
};

#undef MODULE_API
