// Scientific Ways

#include "Utils/ScWUtilsFunctionLibrary.h"

#include "Game/ScWGameState.h"

#include "Engine/PlayerStartPIE.h"

//~ Begin Visibility
bool UScWUtilsFunctionLibrary::IsComponentRenderedFor(UPrimitiveComponent* InComponent, AActor* ForActor)
{
	if (!InComponent->IsVisible())
	{
		return false;
	}
	else
	{
		if (APawn* OwnerPawn = Cast<APawn>(ForActor))
		{
			if (InComponent->bOwnerNoSee && OwnerPawn->IsLocallyViewed())
			{
				return false;
			}
			else if (InComponent->bOnlyOwnerSee && !OwnerPawn->IsLocallyViewed())
			{
				return false;
			}
		}
	}
	return true;
}
//~ End Visibility

//~ Begin Materials
void UScWUtilsFunctionLibrary::ApplyOverrideMaterialsToMeshComponent(UMeshComponent* InMeshComponent, const TMap<int32, UMaterialInterface*>& InOverrideMaterials)
{
	ensureReturn(InMeshComponent);

	for (const auto& SampleKeyValie : InOverrideMaterials)
	{
		InMeshComponent->SetMaterial(SampleKeyValie.Key, SampleKeyValie.Value);
	}
}
//~ End Materials

//~ Begin Teams
/*FGenericTeamId UScWUtilsFunctionLibrary::GetActorTeamId(const AActor* InActor, const bool bInChecked)
{
	ensureReturn(InActor || !bInChecked, FGenericTeamId::NoTeam);
	if (const IGenericTeamAgentInterface* SampleTeamAgent = Cast<IGenericTeamAgentInterface>(InActor))
	{
		return SampleTeamAgent->GetGenericTeamId();
	}
	ensureReturn(!bInChecked, FGenericTeamId::NoTeam);
	return FGenericTeamId::NoTeam;
}

const FName& UScWUtilsFunctionLibrary::GetActorTeamName(const AActor* InActor, const bool bInChecked)
{
	ensureReturn(InActor || !bInChecked, AScWGameState::InvalidTeamName);

	FGenericTeamId TeamId = GetActorTeamId(InActor, bInChecked);
	if (TeamId != FGenericTeamId::NoTeam)
	{
		ensureReturn(InActor, AScWGameState::InvalidTeamName);
		UWorld* World = InActor->GetWorld();
		ensureReturn(World, AScWGameState::InvalidTeamName);

		AScWGameState* GameState = World->GetGameState<AScWGameState>();
		ensureReturn(GameState, AScWGameState::InvalidTeamName);
		return GameState->GetTeamName(TeamId);
	}
	return AScWGameState::InvalidTeamName;
}

TArray<AActor*> UScWUtilsFunctionLibrary::GetAllActorsOfTeam(const UObject* InWCO, const FName& InTeamName, TSubclassOf<AActor> InFilterActorClass)
{
	TArray<AActor*> OutActors;

	ensureReturn(InWCO, OutActors);
	UWorld* World = InWCO->GetWorld();
	ensureReturn(World, OutActors);

	AScWGameState* GameState = World->GetGameState<AScWGameState>();
	ensureReturn(GameState, OutActors);

	FGenericTeamId GenericTeamId = GameState->GetTeamId(InTeamName);
	for (TActorIterator<AActor> It(World, InFilterActorClass ? *InFilterActorClass : AActor::StaticClass()); It; ++It)
	{
		AActor* SampleActor = *It;
		if (IGenericTeamAgentInterface* SampleTeamAgent = Cast<IGenericTeamAgentInterface>(SampleActor))
		{
			if (SampleTeamAgent->GetGenericTeamId() == GenericTeamId)
			{
				OutActors.Add(SampleActor);
			}
		}
	}
	return OutActors;
}

TArray<AActor*> UScWUtilsFunctionLibrary::GetAllActorsOfAnyTeam(const UObject* InWCO, const TSet<FName>& InTeamNameSet, TSubclassOf<AActor> InFilterActorClass)
{
	TArray<AActor*> OutActors;

	ensureReturn(InWCO, OutActors);
	UWorld* World = InWCO->GetWorld();
	ensureReturn(World, OutActors);

	AScWGameState* GameState = World->GetGameState<AScWGameState>();
	ensureReturn(GameState, OutActors);

	TSet<FGenericTeamId> GenericTeamIdSet;
	for (const FName& SampleTeamName : InTeamNameSet)
	{
		ensureContinue(GameState->HasTeamName(SampleTeamName));
		GenericTeamIdSet.Add(GameState->GetTeamId(SampleTeamName));
	}
	for (TActorIterator<AActor> It(World, InFilterActorClass ? *InFilterActorClass : AActor::StaticClass()); It; ++It)
	{
		AActor* SampleActor = *It;
		if (IGenericTeamAgentInterface* SampleTeamAgent = Cast<IGenericTeamAgentInterface>(SampleActor))
		{
			if (GenericTeamIdSet.Contains(SampleTeamAgent->GetGenericTeamId()))
			{
				OutActors.Add(SampleActor);
			}
		}
	}
	return OutActors;
}*/
//~ End Teams

//~ Begin Transforms
FVector UScWUtilsFunctionLibrary::VectorSnappedToGridCenter(const FVector& InVector, const FVector& InGridSize)
{
	FVector OutSnapped;
	OutSnapped.X = InGridSize.X > 0.0f ? FMath::Floor(InVector.X / InGridSize.X) * InGridSize.X + (InGridSize.X * 0.5f) : InVector.X;
	OutSnapped.Y = InGridSize.Y > 0.0f ? FMath::Floor(InVector.Y / InGridSize.Y) * InGridSize.Y + (InGridSize.Y * 0.5f) : InVector.Y;
	OutSnapped.Z = InGridSize.Z > 0.0f ? FMath::Floor(InVector.Z / InGridSize.Z) * InGridSize.Z + (InGridSize.Z * 0.5f) : InVector.Z;
	return OutSnapped;
}
//~ End Transforms

//~ Begin Objects
UObject* UScWUtilsFunctionLibrary::GetObjectDefault(TSubclassOf<UObject> InObjectClass, const bool bInChecked)
{
	ensureReturn(!bInChecked || InObjectClass, nullptr);
	return InObjectClass ? InObjectClass->GetDefaultObject() : nullptr;
}
//~ End Objects
	
//~ Begin Actor Components
UActorComponent* UScWUtilsFunctionLibrary::GetFirstComponentWithTag(const TArray<UActorComponent*>& InComponents, const FName& InTag, int32 InFallbackIndex)
{
	for (UActorComponent* SampleComponent : InComponents)
	{
		ensureContinue(SampleComponent);
		if (SampleComponent->ComponentHasTag(InTag))
		{
			return SampleComponent;
		}
	}
	ensureReturn(InComponents.IsValidIndex(InFallbackIndex), nullptr);
	return InComponents[InFallbackIndex];
}
//~ End Actor Components

//~ Begin Session
bool UScWUtilsFunctionLibrary::IsPlayFromHereEditorSession(const UObject* InWCO)
{
	ensureReturn(InWCO, false);

	for (TActorIterator<APlayerStartPIE> It(InWCO->GetWorld()); It; ++It)
	{
		APlayerStartPIE* PlayFromHereStart = *It;
		ensureContinue(PlayFromHereStart);
		return true;
	}
	return false;
}
//~ End Session
