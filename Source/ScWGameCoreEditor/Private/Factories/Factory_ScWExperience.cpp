// Scientific Ways

#include "Factories/Factory_ScWExperience.h"

#include "Experience/ScWExperience.h"

UFactory_ScWExperience::UFactory_ScWExperience(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
    SupportedClass = UScWExperience::StaticClass();
    bEditAfterNew = true;
    bCreateNew = true;
}

UObject* UFactory_ScWExperience::FactoryCreateNew(UClass* InClass, UObject* InParent, const FName InName,
    const EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn)
{
    check(InClass->IsChildOf(UScWExperience::StaticClass()));
    return NewObject<UScWExperience>(InParent, InClass, InName, InFlags | RF_Transactional, InContext);
}
