// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWPawnDataFragment.generated.h"

#define MODULE_API SCWGAMECORE_API

class UScWPawnExtensionComponent;

/**
 *
 */
UCLASS(MinimalAPI, Const, Abstract, Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew, meta = (DisplayName = "[ScW] Pawn Data Fragment Base"))
class UScWPawnDataFragment : public UObject
{
	GENERATED_BODY()

//~ Begin Initialize
public:
	MODULE_API UScWPawnDataFragment();

	UFUNCTION(Category = "Initialize", BlueprintNativeEvent, meta = (DisplayName = "Initialize Pawn"))
	MODULE_API void BP_InitializePawn(UScWPawnExtensionComponent* InPawnExtComponent) const;
	MODULE_API virtual void BP_InitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const { ensure(false); }

	UFUNCTION(Category = "Initialize", BlueprintNativeEvent, meta = (DisplayName = "Uninitialize Pawn"))
	MODULE_API void BP_UninitializePawn(UScWPawnExtensionComponent* InPawnExtComponent) const;
	MODULE_API virtual void BP_UninitializePawn_Implementation(UScWPawnExtensionComponent* InPawnExtComponent) const { ensure(false); }
//~ End Initialize
};

#undef MODULE_API
