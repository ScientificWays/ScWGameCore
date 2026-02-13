// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWASC_InitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UScWASC_InitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IScWASC_InitInterface
{
	GENERATED_BODY()

	friend class UScWAbilitySystemComponent;

//~ Begin Initialize
public:
	virtual void InitFromASC(class UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) = 0; // IScWASC_InitInterface
//~ End Initialize

//~ Begin Components | AbilitySystem
public:
	class UScWAbilitySystemComponent* GetInitASC() const { return PrivateASC; }
private:
	static void HandleInit(class UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor);
	TObjectPtr<class UScWAbilitySystemComponent> PrivateASC;
//~ End Components | AbilitySystem
};
