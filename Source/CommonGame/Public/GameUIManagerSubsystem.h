// Scientific Ways

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/SoftObjectPtr.h"

#include "GameUIManagerSubsystem.generated.h"

#define MODULE_API COMMONGAME_API

class FSubsystemCollectionBase;
class UCommonLocalPlayer;
class UGameUIPolicy;
class UObject;

/**
 * This manager is intended to be replaced by whatever your game needs to
 * actually create, so this class is abstract to prevent it from being created.
 * 
 * If you just need the basic functionality you will start by sublcassing this
 * subsystem in your own game.
 */
UCLASS(MinimalAPI, Abstract, config = Game)
class UGameUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UGameUIManagerSubsystem() { }
	
	MODULE_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	MODULE_API virtual void Deinitialize() override;
	MODULE_API virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	const UGameUIPolicy* GetCurrentUIPolicy() const { return CurrentPolicy; }
	UGameUIPolicy* GetCurrentUIPolicy() { return CurrentPolicy; }

	MODULE_API virtual void NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer);
	MODULE_API virtual void NotifyPlayerRemoved(UCommonLocalPlayer* LocalPlayer);
	MODULE_API virtual void NotifyPlayerDestroyed(UCommonLocalPlayer* LocalPlayer);

protected:
	MODULE_API void SwitchToPolicy(UGameUIPolicy* InPolicy);

private:
	UPROPERTY(Transient)
	TObjectPtr<UGameUIPolicy> CurrentPolicy = nullptr;

	UPROPERTY(config, EditAnywhere)
	TSoftClassPtr<UGameUIPolicy> DefaultUIPolicyClass;
};

#undef MODULE_API
