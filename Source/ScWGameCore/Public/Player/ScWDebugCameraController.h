// Scientific Ways

#pragma once

#include "Engine/DebugCameraController.h"

#include "ScWDebugCameraController.generated.h"

class UObject;


/**
 *	AScWDebugCameraController
 *
 *	Used for controlling the debug camera when it is enabled via the cheat manager.
 */
UCLASS()
class AScWDebugCameraController : public ADebugCameraController
{
	GENERATED_BODY()

public:
	AScWDebugCameraController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:
	virtual void AddCheats(bool bForce) override;
};
