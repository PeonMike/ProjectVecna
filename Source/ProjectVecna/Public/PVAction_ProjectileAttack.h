// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PVAction.h"
#include "PVAction_ProjectileAttack.generated.h"


class UAnimMontage;
class UParticleSystem;

/**
 * 
 */
UCLASS()
class PROJECTVECNA_API UPVAction_ProjectileAttack : public UPVAction
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* CastingEffect;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);


public:


	virtual void StartAction_Implementation(AActor* Instigator) override;

	UPVAction_ProjectileAttack();
};
