// Scientific Ways

#include "AbilitySystem/ScWGameplayEffectContext.h"

//#include "AbilitySystem/ScWAbilitySourceInterface.h"
#include "Engine/HitResult.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#if UE_WITH_IRIS
#include "Iris/ReplicationState/PropertyNetSerializerInfoRegistry.h"
#include "Serialization/GameplayEffectContextNetSerializer.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameplayEffectContext)

class FArchive;

FScWGameplayEffectContext* FScWGameplayEffectContext::ExtractEffectContext(struct FGameplayEffectContextHandle Handle)
{
	FGameplayEffectContext* BaseEffectContext = Handle.Get();
	if ((BaseEffectContext != nullptr) && BaseEffectContext->GetScriptStruct()->IsChildOf(FScWGameplayEffectContext::StaticStruct()))
	{
		return (FScWGameplayEffectContext*)BaseEffectContext;
	}

	return nullptr;
}

bool FScWGameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);

	// Not serialized for post-activation use:
	// CartridgeID

	return true;
}

#if UE_WITH_IRIS
namespace UE::Net
{
	// Forward to FGameplayEffectContextNetSerializer
	// Note: If FScWGameplayEffectContext::NetSerialize() is modified, a custom NetSerializesr must be implemented as the current fallback will no longer be sufficient.
	UE_NET_IMPLEMENT_FORWARDING_NETSERIALIZER_AND_REGISTRY_DELEGATES(ScWGameplayEffectContext, FGameplayEffectContextNetSerializer);
}
#endif

/*void FScWGameplayEffectContext::SetAbilitySource(const IScWAbilitySourceInterface* InObject, float InSourceLevel)
{
	AbilitySourceObject = MakeWeakObjectPtr(Cast<const UObject>(InObject));
	//SourceLevel = InSourceLevel;
}

const IScWAbilitySourceInterface* FScWGameplayEffectContext::GetAbilitySource() const
{
	return Cast<IScWAbilitySourceInterface>(AbilitySourceObject.Get());
}*/

const UPhysicalMaterial* FScWGameplayEffectContext::GetPhysicalMaterial() const
{
	if (const FHitResult* HitResultPtr = GetHitResult())
	{
		return HitResultPtr->PhysMaterial.Get();
	}
	return nullptr;
}

