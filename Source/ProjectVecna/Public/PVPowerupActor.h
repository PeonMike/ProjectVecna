// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PVGameplayInterface.h"
#include "PVPowerupActor.generated.h"

class USphereComponent;


UCLASS()
class PROJECTVECNA_API APVPowerupActor : public AActor, public IPVGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APVPowerupActor();

protected:


	UPROPERTY(EditAnywhere, Category = "Powerup")
	float RespawnTime;

	UFUNCTION()
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

public:	
	
	void Interact_Implementation(APawn* InstigatorPawn) override;

};
