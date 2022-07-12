// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PVPowerupActor.h"
#include "PVPowerup_HealthPotion.generated.h"

 
class UStaticMeshComponent;


UCLASS()
class PROJECTVECNA_API APVPowerup_HealthPotion : public APVPowerupActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

	APVPowerup_HealthPotion();
};
