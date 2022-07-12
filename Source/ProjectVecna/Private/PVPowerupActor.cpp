// Fill out your copyright notice in the Description page of Project Settings.


#include "PVPowerupActor.h"
#include "Components/SphereComponent.h"

// Sets default values
APVPowerupActor::APVPowerupActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;
}


void APVPowerupActor::ShowPowerup()
{
	SetPowerupState(true);
}

void APVPowerupActor::HideAndCooldownPowerup()
{
	SetPowerupState(false);

	FTimerHandle TimerHandle_RespawnTimer;
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &APVPowerupActor::ShowPowerup, RespawnTime);
}

void APVPowerupActor::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	// Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}

void APVPowerupActor::Interact_Implementation(APawn * InstigatorPawn)
{
}



