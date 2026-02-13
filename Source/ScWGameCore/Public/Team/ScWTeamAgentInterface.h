// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWTeamAgentInterface.generated.h"

#define MODULE_API SCWGAMECORE_API

template <typename InterfaceType> class TScriptInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnScWTeamIndexChangedDelegate, UObject*, ObjectChangingTeam, int32, OldTeamID, int32, NewTeamID);

inline int32 GenericTeamIdToInteger(FGenericTeamId ID)
{
	return (ID == FGenericTeamId::NoTeam) ? INDEX_NONE : (int32)ID;
}

inline FGenericTeamId IntegerToGenericTeamId(int32 ID)
{
	return (ID == INDEX_NONE) ? FGenericTeamId::NoTeam : FGenericTeamId((uint8)ID);
}

/** Interface for actors which can be associated with teams */
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UScWTeamAgentInterface : public UGenericTeamAgentInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IScWTeamAgentInterface : public IGenericTeamAgentInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual FOnScWTeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() { return nullptr; }

	static MODULE_API void ConditionalBroadcastTeamChanged(TScriptInterface<IScWTeamAgentInterface> This, FGenericTeamId OldTeamID, FGenericTeamId NewTeamID);
	
	FOnScWTeamIndexChangedDelegate& GetTeamChangedDelegateChecked()
	{
		FOnScWTeamIndexChangedDelegate* Result = GetOnTeamIndexChangedDelegate();
		check(Result);
		return *Result;
	}
};

#undef MODULE_API
