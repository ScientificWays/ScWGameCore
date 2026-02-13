// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWAnimationsFunctionLibrary.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Animations Function Library"))
class UScWAnimationsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static MODULE_API const FName MontageDefaultGroupName;

//~ Begin Anim Instances
public:

	UFUNCTION(Category = "Anim Instances", BlueprintCallable, BlueprintPure)
	static MODULE_API class UScWAnimInstance_FirstPerson* GetCharacterFirstPersonAnimInstance(class ACharacter* InCharacter, const bool bInChecked = true);

	UFUNCTION(Category = "Anim Instances", BlueprintCallable, BlueprintPure)
	static MODULE_API class UScWAnimInstance_ThirdPerson* GetCharacterThirdPersonAnimInstance(class ACharacter* InCharacter, const bool bInChecked = true);
//~ End Anim Instances
	
//~ Begin Montages
public:

	UFUNCTION(Category = "Montages", BlueprintCallable, BlueprintPure, meta = (AdvancedDisplay = "InFallbackValue", KeyWords = "GetDuration"))
	static MODULE_API float GetMontagePlayLength(const UAnimMontage* InMontage, float InTimeMul = 1.0f, float InFallbackValue = 0.0f);

	UFUNCTION(Category = "Montages", BlueprintCallable, BlueprintPure, meta = (AdvancedDisplay = "InFallbackValue", KeyWords = "GetDuration, GetSectionLength"))
	static MODULE_API float GetMontageSectionLengthByIndex(const UAnimMontage* InMontage, int32 InIndex, float InTimeMul = 1.0f, float InFallbackValue = 0.0f);

	UFUNCTION(Category = "Montages", BlueprintCallable, BlueprintPure, meta = (AutoCreateRefTerm = "InName", AdvancedDisplay = "InFallbackValue", KeyWords = "GetDuration, GetSectionLength"))
	static MODULE_API float GetMontageSectionLengthByName(const UAnimMontage* InMontage, const FName& InName, float InTimeMul = 1.0f, float InFallbackValue = 0.0f);

	UFUNCTION(Category = "Montages | Character Data", BlueprintCallable, BlueprintPure, meta = (AdvancedDisplay = "InFallbackValue", KeyWords = "GetDuration"))
	static MODULE_API float GetMontagePlayLengthFromData(const struct FScWCharacterMontageData& InCharacterMontageData, float InFallbackValue = 0.0f);

	UFUNCTION(Category = "Montages | Character Data", BlueprintCallable, BlueprintPure, meta = (AdvancedDisplay = "InFallbackValue", KeyWords = "GetDuration, GetSectionLength"))
	static MODULE_API float GetMontageSectionLengthByIndexFromData(const struct FScWCharacterMontageData& InCharacterMontageData, int32 InIndex, float InFallbackValue = 0.0f);

	UFUNCTION(Category = "Montages | Character Data", BlueprintCallable, BlueprintPure, meta = (AutoCreateRefTerm = "InName", AdvancedDisplay = "InFallbackValue", KeyWords = "GetDuration, GetSectionLength"))
	static MODULE_API float GetMontageSectionLengthByNameFromData(const struct FScWCharacterMontageData& InCharacterMontageData, const FName& InName, float InFallbackValue = 0.0f);

	UFUNCTION(Category = "Montages | Character Data", BlueprintCallable, meta = (ReturnDisplayName = "Out Max Duration", KeyWords = "PlayMontageData, PlayCharacterMontageData"))
	static MODULE_API float PlayCharacterMontagesFromData(class ACharacter* InCharacter, const struct FScWCharacterMontageData& InCharacterMontageData, const bool bInStopAllMontages = true);
//~ End Montages

//~ Begin Static Data
public:
	
	UFUNCTION(Category = "Static Data", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API void SetCharacterDefaultStaticAnimationData(class ACharacter* InCharacter, const struct FScWFirstPersonStaticAnimationData& InFirstPersonStaticAnimationData, const struct FScWThirdPersonStaticAnimationData& InThirdPersonStaticAnimationData, const bool bInApplyDefaultStaticAnimationData);
	
	UFUNCTION(Category = "Static Data", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API void ToggleCharacterHolsterStaticAnimationData(class ACharacter* InCharacter, const bool bInUseHolster, const float InBlendTime, const bool bInFirstPerson = true, const bool bInThirdPerson = true);

	UFUNCTION(Category = "Static Data", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API void ToggleCharacterAlternativeBasePose(class ACharacter* InCharacter, const bool bInUseAlternative, const float InBlendTime, const bool bInFirstPerson = true, const bool bInThirdPerson = true);

	UFUNCTION(Category = "Static Data", BlueprintCallable, BlueprintCosmetic)
	static MODULE_API void ToggleCharacterEnableIdleAnimation(class ACharacter* InCharacter, const bool bInEnable, const bool bInFirstPerson = true, const bool bInThirdPerson = true);
//~ End Static Data
};

#undef MODULE_API
