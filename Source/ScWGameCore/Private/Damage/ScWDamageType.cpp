// Scientific Ways

#include "Damage/ScWDamageType.h"

#include "Damage/ScWAttributeHealthComponent.h"

//#include "ComboSystem/ScWComboData.h"

#include "Engine/DamageEvents.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWDamageType)

UScWDamageType::UScWDamageType()
{
	DisplayName = FText::FromString(TEXT("[Please set DisplayName]"));
	AnalyticsName = TEXT("[Please set AnalyticsName]");

	ApplyDamageGameplayEffectDuration = 0.05f;

	bApplyImpactImpulse = true;
	ImpactImpulsePerDamagePoint = 20.0f;
	ImpactImpulseMassFactor = 0.2f;
}

//~ Begin Statics
float UScWDamageType::ApplyPointDamage(AActor* InSourceActor, AActor* InTargetActor, float InDamage, const FVector& InHitFromDirection, const FHitResult& InHitResult, AController* InInstigator, TSubclassOf<UDamageType> InDamageTypeClass)
{
	if (InTargetActor == nullptr)
	{
		return 0.0f;
	}
	if (InDamage <= 0.0f)
	{
		return 0.0f;
	}
	const TSubclassOf<UDamageType> ValidDamageTypeClass = InDamageTypeClass ? InDamageTypeClass : TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FPointDamageEvent PointDamageEvent = { InDamage, InHitResult, InHitFromDirection, ValidDamageTypeClass };

	return InTargetActor->TakeDamage(InDamage, PointDamageEvent, InInstigator, InSourceActor);
}

void UScWDamageType::MakeMinimalInfoDamageImpactHitResult(AActor* InSourceActor, UPrimitiveComponent* InSourceComponent, APawn* InInstigatorPawn, AActor* InDamagedActor, UPrimitiveComponent* InDamagedComponent, FHitResult& OutHitResult)
{
	ensure(InDamagedComponent);
	FVector SourceLocation = FVector::ZeroVector;

	if (InSourceComponent)
	{
		SourceLocation = InSourceComponent->GetComponentLocation();
	}
	else if (InSourceActor)
	{
		SourceLocation = InSourceActor->GetActorLocation();
	}
	else
	{
		ensure(false);
	}
	if (InInstigatorPawn)
	{
		SourceLocation = FMath::Lerp(SourceLocation, InInstigatorPawn->GetPawnViewLocation(), 0.5f);
	}
	FVector ImpactLocation = FVector::ZeroVector;

	if (InDamagedComponent)
	{
		ImpactLocation = InDamagedComponent->GetComponentLocation();
	}
	else if (InDamagedActor)
	{
		ImpactLocation = InDamagedActor->GetActorLocation();
	}
	else
	{
		ensure(false);
	}
	OutHitResult = FHitResult(InDamagedActor, InDamagedComponent, ImpactLocation, (SourceLocation - ImpactLocation).GetSafeNormal());
	OutHitResult.TraceStart = SourceLocation;
	OutHitResult.TraceEnd = ImpactLocation;
	OutHitResult.Time = 1.0f;
	OutHitResult.Distance = FVector::Distance(SourceLocation, ImpactLocation);
}
//~ End Statics

//~ Begin Impact
void UScWDamageType::ApplyImpactImpulseToCharacterMovement(UCharacterMovementComponent* InCharacterMovement, const FHitResult& InHitResult) const
{
	ensureReturn(InCharacterMovement);
	InCharacterMovement->Launch(BP_GetImpactImpulseForHit(InCharacterMovement, InHitResult));
}

void UScWDamageType::ApplyImpactImpulseToPhysicsBody(UPrimitiveComponent* InBody, const FHitResult& InHitResult) const
{
	ensureReturn(InBody);
	InBody->AddImpulseAtLocation(BP_GetImpactImpulseForHit(InBody, InHitResult), InHitResult.ImpactPoint, InHitResult.BoneName);
}

FVector UScWDamageType::BP_GetImpactImpulseForHit_Implementation(const UActorComponent* InTargetComponent, const FHitResult& InHitResult) const
{
	ensureReturn(InTargetComponent, FVector::ZeroVector);

	float OutImpulse = DamageImpulse;

	AActor* OwnerActor = InTargetComponent->GetOwner();
	ensureReturn(OwnerActor, FVector::ZeroVector);

	if (const UScWAttributeHealthComponent* TargetHealthComponent = OwnerActor->GetComponentByClass<UScWAttributeHealthComponent>())
	{
		OutImpulse = TargetHealthComponent->GetLastAppliedDamage() * ImpactImpulsePerDamagePoint;

		/*const FReceivedDamageData& LastAppliedDamageData = TargetHealthComponent->GetLastAppliedDamageData();
		if (const UScWAbilitySystemComponent* AttackerASC = LastAppliedDamageData.TryGetAttackerBaseASC())
		{
			if (const UScWComboData* AttackerRelevantCombo = AttackerASC->GetRelevantCombo())
			{
				OutImpulse *= AttackerRelevantCombo->DamageImpactImpulseMul;
			}
		}*/
	}
	if (const UCharacterMovementComponent* TargetCharacterMovement = Cast<UCharacterMovementComponent>(InTargetComponent))
	{
		if (ImpactImpulseMassFactor > 0.0f)
		{
			OutImpulse /= FMath::Max(FMath::Lerp(1.0f, TargetCharacterMovement->Mass, ImpactImpulseMassFactor), 0.001f);
		}
	}
	return -InHitResult.ImpactNormal * OutImpulse;
}
//~ End Impact
