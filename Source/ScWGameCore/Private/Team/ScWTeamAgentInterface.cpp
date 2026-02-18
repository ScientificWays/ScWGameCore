// Scientific Ways

#include "Team/ScWTeamAgentInterface.h"

#include "Tags/ScWCoreTags.h"

#include "UObject/ScriptInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWTeamAgentInterface)

UScWTeamAgentInterface::UScWTeamAgentInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

const FGameplayTag IScWTeamAgentInterface::TeamNoneTag = FScWCoreTags::Team_None;

void IScWTeamAgentInterface::ConditionalBroadcastTeamChanged(TScriptInterface<IScWTeamAgentInterface> This, const FGameplayTag& InPrevTeamTag, const FGameplayTag& InNewTeamTag)
{
	if (InPrevTeamTag != InNewTeamTag)
	{
		UObject* ThisObj = This.GetObject();
		UE_LOG(LogScWGameCore, Verbose, TEXT("[%s] %s assigned team %s"), *GetClientServerContextString(ThisObj), *GetPathNameSafe(ThisObj), *InNewTeamTag.ToString());

		This.GetInterface()->GetTeamChangedDelegateChecked().Broadcast(ThisObj, InPrevTeamTag, InNewTeamTag);
	}
}

