// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWTypes_Animation.generated.h"

#define MODULE_API SCWGAMECORE_API

USTRUCT(BlueprintType, meta = (DisplayName = "[ScW] FirstPerson StaticAnimationData"))
struct FScWFirstPersonStaticAnimationData
{
	GENERATED_BODY()

	UPROPERTY(Category = "Base", BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UAnimSequence> BasePose = nullptr;
	
	UPROPERTY(Category = "Base", BlueprintReadOnly, EditAnywhere, meta = (ClampMin = "0.0"))
	bool bBasePosePitchIK = true;
	
	UPROPERTY(Category = "Base", BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bBasePosePitchIK", ClampMin = "0.0"))
	float BasePosePitchIKScale = 0.05f;

	UPROPERTY(Category = "Base", BlueprintReadOnly, EditAnywhere, meta = (ClampMin = "0.0"))
	float BasePoseWalkBlendAlphaScale = 0.5f;
	
	UPROPERTY(Category = "Alternative", BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UAnimSequence> AlternativeBasePose = nullptr;
	
	UPROPERTY(Category = "Alternative", BlueprintReadOnly, EditAnywhere, meta = (ClampMin = "0.0"))
	bool bAlternativeBasePosePitchIK = false;
	
	UPROPERTY(Category = "Alternative", BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bAlternativeBasePosePitchIK", ClampMin = "0.0"))
	float AlternativeBasePosePitchIKScale = 0.05f;

	UPROPERTY(Category = "Alternative", BlueprintReadOnly, EditAnywhere, meta = (ClampMin = "0.0"))
	float AlternativeBasePoseWalkBlendAlphaScale = 0.05f;

	bool MODULE_API IsValid() const { return BasePose && AlternativeBasePose; }
	static MODULE_API const FScWFirstPersonStaticAnimationData None;
};

USTRUCT(BlueprintType, meta = (DisplayName = "[ScW] ThirdPerson StaticAnimationData"))
struct FScWThirdPersonStaticAnimationData
{
	GENERATED_BODY()
		
	UPROPERTY(Category = "UpperBody", BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UAnimSequence> UpperBodyIdle = nullptr;

	UPROPERTY(Category = "UpperBody", BlueprintReadOnly, EditAnywhere)
	TObjectPtr<class UAimOffsetBlendSpace> UpperBodyAimOffset = nullptr;

	UPROPERTY(Category = "UpperBody", BlueprintReadOnly, EditAnywhere)
	TObjectPtr<class UAimOffsetBlendSpace> UpperBodyAlternativeAimOffset = nullptr;

	bool MODULE_API IsValid() const { return UpperBodyIdle && UpperBodyAimOffset && UpperBodyAlternativeAimOffset; }
	static MODULE_API const FScWThirdPersonStaticAnimationData None;
};

USTRUCT(BlueprintType, meta = (DisplayName = "[ScW] Equipment StaticAnimationData"))
struct FScWEquipmentStaticAnimationData
{
	GENERATED_BODY()

	UPROPERTY(Category = "Static", BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UAnimSequence> BasePose = nullptr;

	UPROPERTY(Category = "Static", BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UAnimSequence> AlternativeBasePose = nullptr;

	MODULE_API bool IsValid() const { return BasePose && AlternativeBasePose; }
	static MODULE_API const FScWEquipmentStaticAnimationData None;
};

UENUM(BlueprintType, meta = (DisplayName = "[ScW] Timing Montage Type"))
enum class EScWTimingMontageType : uint8
{
	FirstPerson,
	ThirdPerson,
	ActiveEquipment
};

USTRUCT(BlueprintType, meta = (DisplayName = "[ScW] Character MontageData"))
struct FScWCharacterMontageData
{
	GENERATED_BODY()

	UPROPERTY(Category = "Montage", EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "FP: Character Montage"))
	TObjectPtr<UAnimMontage> FirstPersonMontage = nullptr;

	UPROPERTY(Category = "Montage", EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TP: Character Montage"))
	TObjectPtr<UAnimMontage> ThirdPersonMontage = nullptr;
	
	UPROPERTY(Category = "Montage", EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Equipment Montage"))
	TObjectPtr<UAnimMontage> ActiveEquipmentMontage = nullptr;

	UPROPERTY(Category = "Montage", EditAnywhere, BlueprintReadWrite)
	EScWTimingMontageType TimingMontageType = EScWTimingMontageType::FirstPerson;

	UPROPERTY(Category = "Shake", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> FirstPersonCameraShake = nullptr;

	UPROPERTY(Category = "Time", EditAnywhere, BlueprintReadWrite)
	float TimeMul = 1.0f;

	MODULE_API UAnimMontage* GetRelevantTimingMontage() const;
};

#undef MODULE_API
