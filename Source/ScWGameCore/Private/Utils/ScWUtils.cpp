// Scientific Ways

#include "Utils/ScWUtils.h"

FString GetClientServerContextString(UObject* InContext)
{
	ENetRole Role = ROLE_None;

	if (AActor* Actor = Cast<AActor>(InContext))
	{
		Role = Actor->GetLocalRole();
	}
	else if (UActorComponent* Component = Cast<UActorComponent>(InContext))
	{
		Role = Component->GetOwnerRole();
	}
	if (Role != ROLE_None)
	{
		return (Role == ROLE_Authority) ? TEXT("Server") : TEXT("Client");
	}
	else
	{
#if WITH_EDITOR
		if (GIsEditor)
		{
			extern ENGINE_API FString GPlayInEditorContextString;
			return GPlayInEditorContextString;
		}
#endif
	}
	return TEXT("[]");
}
