// Scientific Ways

#include "Factories/Factory_ScWPawnData.h"

#include "Character/ScWPawnData.h"

UFactory_ScWPawnData::UFactory_ScWPawnData(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
    SupportedClass = UScWPawnData::StaticClass();
    bEditAfterNew = true;
    bCreateNew = true;
}

UObject* UFactory_ScWPawnData::FactoryCreateNew(UClass* InClass, UObject* InParent, const FName InName,
    const EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn)
{
    check(InClass->IsChildOf(UScWPawnData::StaticClass()));
    return NewObject<UScWPawnData>(InParent, InClass, InName, InFlags | RF_Transactional, InContext);
}
