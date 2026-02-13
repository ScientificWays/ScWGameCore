// Scientific Ways

#pragma once

#include "GameplayEffectTypes.h"

#include "ScWGameplayEffectContext.generated.h"

#define MODULE_API SCWGAMECORE_API

class AActor;
class FArchive;
class IScWAbilitySourceInterface;
class UObject;
class UPhysicalMaterial;

USTRUCT()
struct FScWGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

	FScWGameplayEffectContext()
		: FGameplayEffectContext()
	{
	}

	FScWGameplayEffectContext(AActor* InInstigator, AActor* InEffectCauser)
		: FGameplayEffectContext(InInstigator, InEffectCauser)
	{
	}

	/** Returns the wrapped FScWGameplayEffectContext from the handle, or nullptr if it doesn't exist or is the wrong type */
	static MODULE_API FScWGameplayEffectContext* ExtractEffectContext(struct FGameplayEffectContextHandle Handle);

	/** Sets the object used as the ability source */
	//void SetAbilitySource(const IScWAbilitySourceInterface* InObject, float InSourceLevel);

	/** Returns the ability source interface associated with the source object. Only valid on the authority. */
	//const IScWAbilitySourceInterface* GetAbilitySource() const;

	virtual FGameplayEffectContext* Duplicate() const override
	{
		FScWGameplayEffectContext* NewContext = new FScWGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FScWGameplayEffectContext::StaticStruct();
	}

	/** Overridden to serialize new fields */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	/** Returns the physical material from the hit result if there is one */
	const UPhysicalMaterial* GetPhysicalMaterial() const;

public:
	/** ID to allow the identification of multiple bullets that were part of the same cartridge */
	UPROPERTY()
	int32 CartridgeID = -1;

protected:
	/** Ability Source object (should implement IScWAbilitySourceInterface). NOT replicated currently */
	UPROPERTY()
	TWeakObjectPtr<const UObject> AbilitySourceObject;
};

template<>
struct TStructOpsTypeTraits<FScWGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FScWGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

#undef MODULE_API
