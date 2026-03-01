// Scientific Ways

#pragma once

#include "ModularPlayerController.h"

#include "CommonPlayerController.generated.h"

#define MODULE_API COMMONGAME_API

class APawn;
class UObject;

UCLASS(MinimalAPI, Config = Game)
class ACommonPlayerController : public AModularPlayerController
{
	GENERATED_BODY()

public:
	MODULE_API ACommonPlayerController(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	MODULE_API virtual void ReceivedPlayer() override;	
	MODULE_API virtual void SetPawn(APawn* InPawn) override;
	MODULE_API virtual void OnPossess(class APawn* APawn) override;
	MODULE_API virtual void OnUnPossess() override;
	
protected:
	MODULE_API virtual void OnRep_PlayerState() override;
};

#undef MODULE_API
