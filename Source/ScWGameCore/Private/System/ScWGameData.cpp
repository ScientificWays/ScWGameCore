// Scientific Ways

#include "System/ScWGameData.h"

#include "System/ScWAssetManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameData)

UScWGameData::UScWGameData()
{
}

const UScWGameData& UScWGameData::UScWGameData::Get()
{
	return UScWAssetManager::Get().GetGameData();
}
