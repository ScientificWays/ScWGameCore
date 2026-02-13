// Scientific Ways

#pragma once

#include "Engine/DataAsset.h"

#include "ScWGameData.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *	Non-mutable data asset that contains global game data.
 */
UCLASS(MinimalAPI, BlueprintType, Const, Meta = (DisplayName = "[ScW] Game Data", ShortTooltip = "Data asset containing global game data."))
class UScWGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	MODULE_API UScWGameData();

	// Returns the loaded game data.
	static MODULE_API const UScWGameData& Get();

public:

	// Gameplay effect used to apply damage.  Uses SetByCaller for the damage magnitude.
	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects", meta = (DisplayName = "Damage Gameplay Effect (SetByCaller)"))
	TSoftClassPtr<class UGameplayEffect> DamageGameplayEffect_SetByCaller;

	// Gameplay effect used to apply healing.  Uses SetByCaller for the healing magnitude.
	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects", meta = (DisplayName = "Heal Gameplay Effect (SetByCaller)"))
	TSoftClassPtr<class UGameplayEffect> HealGameplayEffect_SetByCaller;

	// Gameplay effect used to add and remove dynamic tags.
	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects")
	TSoftClassPtr<class UGameplayEffect> DynamicTagGameplayEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects")
	TSoftClassPtr<class UGameplayEffect> SetHealthGameplayEffect_SetByCaller;

	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects")
	TSoftClassPtr<class UGameplayEffect> AddHealthGameplayEffect_SetByCaller;

	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects")
	TSoftClassPtr<class UGameplayEffect> DeadStateGameplayEffect;
};

#undef MODULE_API
