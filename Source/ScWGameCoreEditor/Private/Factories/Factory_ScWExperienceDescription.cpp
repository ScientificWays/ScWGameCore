// Scientific Ways

#include "Factories/Factory_ScWExperienceDescription.h"

#include "Experience/ScWExperienceDescription.h"

UFactory_ScWExperienceDescription::UFactory_ScWExperienceDescription(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
    SupportedClass = UScWExperienceDescription::StaticClass();
    bEditAfterNew = true;
    bCreateNew = true;
}

UObject* UFactory_ScWExperienceDescription::FactoryCreateNew(UClass* InClass, UObject* InParent, const FName InName,
    const EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn)
{
    check(InClass->IsChildOf(UScWExperienceDescription::StaticClass()));
    return NewObject<UScWExperienceDescription>(InParent, InClass, InName, InFlags | RF_Transactional, InContext);
}
