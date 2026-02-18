// Scientific Ways

#include "Factories/Factory_ScWExperienceActionSet.h"

#include "Experience/ScWExperienceActionSet.h"

UFactory_ScWExperienceActionSet::UFactory_ScWExperienceActionSet(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
    SupportedClass = UScWExperienceActionSet::StaticClass();
    bEditAfterNew = true;
    bCreateNew = true;
}

UObject* UFactory_ScWExperienceActionSet::FactoryCreateNew(UClass* InClass, UObject* InParent, const FName InName,
    const EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn)
{
    check(InClass->IsChildOf(UScWExperienceActionSet::StaticClass()));
    return NewObject<UScWExperienceActionSet>(InParent, InClass, InName, InFlags | RF_Transactional, InContext);
}
