// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWDamageType.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *
 */
UCLASS(Const, Blueprintable, BlueprintType, meta = (DisplayName = "[ScW] Damage Type"))
class UScWDamageType : public UDamageType
{
	GENERATED_BODY()

public:	

	UScWDamageType();

//~ Begin Statics
public:

	UFUNCTION(Category = "Statics", BlueprintCallable, BlueprintAuthorityOnly, meta = (DisplayName = "[ScW] Apply Point Damage"))
	static MODULE_API float ApplyPointDamage(AActor* InSourceActor, AActor* InTargetActor, float InDamage, const FVector& InHitFromDirection, const FHitResult& InHitResult, AController* InInstigator, TSubclassOf<UDamageType> InDamageTypeClass);

	UFUNCTION(Category = "Statics", BlueprintCallable, BlueprintPure, meta = (KeyWords = "GetHitResult, GetMinimalInfoHitResult, GetMinimalHitResult, MakeHitResult, MakeMinimalHitResult"))
	static MODULE_API void MakeMinimalInfoDamageImpactHitResult(AActor* InSourceActor, UPrimitiveComponent* InSourceComponent, APawn* InInstigatorPawn, AActor* InDamagedActor, UPrimitiveComponent* InDamagedComponent, FHitResult& OutHitResult);
//~ End Statics

//~ Begin Info
public:

	UPROPERTY(Category = "Info", EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(Category = "Info", EditDefaultsOnly, BlueprintReadOnly)
	FString AnalyticsName;

	UPROPERTY(Category = "Info", EditDefaultsOnly, BlueprintReadOnly, meta = (AssetBundles = "Game"))
	TSoftObjectPtr<UTexture2D> Image;
//~ End UI

//~ Begin GAS
public:

	UPROPERTY(Category = "GAS", EditDefaultsOnly, BlueprintReadOnly, meta = (AssetBundles = "Game"))
	TSubclassOf<UGameplayEffect> ApplyDamageGameplayEffectClass;

	UPROPERTY(Category = "GAS", EditDefaultsOnly, BlueprintReadOnly)
	float ApplyDamageGameplayEffectDuration;
//~ End GAS

//~ Begin Impact
public:
	void ApplyImpactImpulseToCharacterMovement(class UCharacterMovementComponent* InCharacterMovement, const FHitResult& InHitResult) const;
	void ApplyImpactImpulseToPhysicsBody(UPrimitiveComponent* InBody, const FHitResult& InHitResult) const;

	UPROPERTY(Category = "Impact", EditDefaultsOnly, BlueprintReadOnly)
	bool bApplyImpactImpulse;

	UPROPERTY(Category = "Impact", EditDefaultsOnly, BlueprintReadOnly)
	float ImpactImpulsePerDamagePoint;

	UPROPERTY(Category = "Impact", EditDefaultsOnly, BlueprintReadOnly)
	float ImpactImpulseMassFactor;

protected:

	UFUNCTION(Category = "Impact", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Get Impact Impulse for Hit"))
	FVector BP_GetImpactImpulseForHit(const UActorComponent* InTargetComponent, const FHitResult& InHitResult) const;
//~ End Impact
};

#undef MODULE_API
