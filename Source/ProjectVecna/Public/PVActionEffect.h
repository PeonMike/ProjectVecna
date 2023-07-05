// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PVAction.h"
#include "PVActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVECNA_API UPVActionEffect : public UPVAction
{
	GENERATED_BODY()

public:

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Duration;

	/* Time between 'ticks' to apply effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Period;

	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BlueprintNativeEvent, Category = "Effect")
	void ExecutePeriodicEffect(AActor* Instigator);

public:

	UFUNCTION(BlueprintCallable, Category = "Action")
	float GetTimeRemaning() const;

	UPVActionEffect();
};
