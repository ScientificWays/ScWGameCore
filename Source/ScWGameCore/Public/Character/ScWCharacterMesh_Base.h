// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "AbilitySystem/ScWASC_InitInterface.h"

#include "ScWCharacterMesh_Base.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, Abstract, meta = (DisplayName = "[ScW] Character Mesh Base (Component)"))
class UScWCharacterMesh_Base : public USkeletalMeshComponent, public IScWASC_InitInterface
{
	GENERATED_BODY()

public:

	UScWCharacterMesh_Base();

//~ Begin Initialize
protected:
	virtual void OnRegister() override; // UActorComponent
	virtual void BeginPlay() override; // UActorComponent
public:
	virtual void InitFromASC(class UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) override; // IScWASC_InitInterface
//~ End Initialize
};
