// Scientific Ways

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "ScWUtilsFunctionLibrary.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Gameplay Function Library"))
class UScWUtilsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

//~ Begin Visibility
public:

	UFUNCTION(Category = "Visibility", BlueprintCallable, BlueprintPure)
	static MODULE_API bool IsComponentRenderedFor(UPrimitiveComponent* InComponent, AActor* ForActor);
//~ End Visibility
	
//~ Begin Materials
public:

	UFUNCTION(Category = "Materials", BlueprintCallable)
	static MODULE_API void ApplyOverrideMaterialsToMeshComponent(UMeshComponent* InMeshComponent, const TMap<int32, UMaterialInterface*>& InOverrideMaterials);
//~ End Materials
	
//~ Begin Teams
public:

	/*UFUNCTION(Category = "Teams", BlueprintCallable, meta = (KeyWords = "GetTeamOfActor"))
	static MODULE_API FGenericTeamId GetActorTeamId(const AActor* InActor, const bool bInChecked = false);

	UFUNCTION(Category = "Teams", BlueprintCallable, meta = (KeyWords = "GetTeamOfActor"))
	static MODULE_API const FName& GetActorTeamName(const AActor* InActor, const bool bInChecked = false);

	UFUNCTION(Category = "Teams", BlueprintCallable, meta = (WorldContext = "InWCO", KeyWords = "GetActorsOfTeam, GetCharactersOfTeam, GetAllCharactersOfTeam", AutoCreateRefTerm = "InTeamName", DeterminesOutputType = "InFilterActorClass"))
	static MODULE_API TArray<AActor*> GetAllActorsOfTeam(const UObject* InWCO, const FName& InTeamName, TSubclassOf<AActor> InFilterActorClass = nullptr);

	UFUNCTION(Category = "Teams", BlueprintCallable, meta = (WorldContext = "InWCO", KeyWords = "GetActorsOfTeamSet, GetCharactersOfTeamSet, GetAllCharactersOfTeamSet", AutoCreateRefTerm = "InTeamName", DeterminesOutputType = "InFilterActorClass"))
	static MODULE_API TArray<AActor*> GetAllActorsOfAnyTeam(const UObject* InWCO, const TSet<FName>& InTeamNameSet, TSubclassOf<AActor> InFilterActorClass = nullptr);*/
//~ End Teams

//~ Begin Transforms
public:

	UFUNCTION(Category = "Transforms", BlueprintCallable, BlueprintPure, meta = (KeyWords = "Location, Position, Middle", AutoCreateRefTerm = "InVector, InGridSize"))
	static MODULE_API FVector VectorSnappedToGridCenter(const FVector& InVector, const FVector& InGridSize);
//~ End Transforms

//~ Begin Objects
public:

	UFUNCTION(Category = "Objects", BlueprintCallable, BlueprintPure, meta = (DeterminesOutputType = "InObjectClass"))
	static MODULE_API UObject* GetObjectDefault(TSubclassOf<UObject> InObjectClass, const bool bInChecked = true);
//~ End Objects
	
//~ Begin Actor Components
public:

	UFUNCTION(Category = "Actor Components", BlueprintCallable, BlueprintPure, meta = (DeterminesOutputType = "InComponents"))
	static MODULE_API UActorComponent* GetFirstComponentWithTag(const TArray<UActorComponent*>& InComponents, const FName& InTag, int32 InFallbackIndex = 0);
//~ End Actor Components

//~ Begin Session
public:

	UFUNCTION(Category = "Session", BlueprintCallable, meta = (WorldContext = "InWCO", ExpandBoolAsExecs = "ReturnValue"))
	static MODULE_API bool IsPlayFromHereEditorSession(const UObject* InWCO);
//~ End Session
};

#undef MODULE_API
