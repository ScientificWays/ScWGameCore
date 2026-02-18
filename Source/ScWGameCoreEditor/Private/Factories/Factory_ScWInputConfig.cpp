// Scientific Ways

#include "Factories/Factory_ScWInputConfig.h"

#include "Input/ScWInputConfig.h"

UFactory_ScWInputConfig::UFactory_ScWInputConfig(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
    SupportedClass = UScWInputConfig::StaticClass();
    bEditAfterNew = true;
    bCreateNew = true;
}

UObject* UFactory_ScWInputConfig::FactoryCreateNew(UClass* InClass, UObject* InParent, const FName InName,
    const EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn)
{
    check(InClass->IsChildOf(UScWInputConfig::StaticClass()));
    return NewObject<UScWInputConfig>(InParent, InClass, InName, InFlags | RF_Transactional, InContext);
}
