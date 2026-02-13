// Scientific Ways

#pragma once

#include "CoreMinimal.h"

#include "ScWWrapper_VectorArray.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
* 
*/
UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "[ScW] Wrapper (VectorArray)"))
class UScWWrapper_VectorArray : public UObject
{
	GENERATED_BODY()

public:	

	UScWWrapper_VectorArray();
	
//~ Begin Get
public:

	UFUNCTION(Category = "Get", BlueprintCallable, BlueprintPure, meta = (DefaultToSelf = "InOuter"))
	static MODULE_API UScWWrapper_VectorArray* CreateVectorArrayWrapper(UObject* InOuter, const TArray<FVector>& InVectorArray);
//~ End Get

//~ Begin Data
public:

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite)
	TArray<FVector> VectorArray;
//~ End Data
};

#undef MODULE_API
