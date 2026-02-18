// Scientific Ways

#pragma once

#include "ScWGameCoreEditor.h"

#include "Factory_ScWExperienceActionSet.generated.h"

UCLASS()
class SCWGAMECOREEDITOR_API UFactory_ScWExperienceActionSet : public UFactory
{
    GENERATED_BODY()

public:
    UFactory_ScWExperienceActionSet(const FObjectInitializer& InObjectInitializer);

    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags,
        UObject* InContext, FFeedbackContext* InWarn) override; // UFactory
};
