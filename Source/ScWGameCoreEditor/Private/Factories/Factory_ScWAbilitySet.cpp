// Scientific Ways

#include "Factories/Factory_ScWAbilitySet.h"

#include "AbilitySystem/ScWAbilitySet.h"

UFactory_ScWAbilitySet::UFactory_ScWAbilitySet(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
    SupportedClass = UScWAbilitySet::StaticClass();
    bEditAfterNew = true;
    bCreateNew = true;
}

UObject* UFactory_ScWAbilitySet::FactoryCreateNew(UClass* InClass, UObject* InParent, const FName InName,
    const EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn)
{
    check(InClass->IsChildOf(UScWAbilitySet::StaticClass()));
    return NewObject<UScWAbilitySet>(InParent, InClass, InName, InFlags | RF_Transactional, InContext);
}
