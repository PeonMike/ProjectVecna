// Fill out your copyright notice in the Description page of Project Settings.


#include "PVAttributeComponent.h"

// Sets default values for this component's properties
UPVAttributeComponent::UPVAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;
}



bool UPVAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UPVAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}


float UPVAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}



bool UPVAttributeComponent::ApplyHealthChange(float Delta)
{
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta); // @fixme: Still nullptr for InstigatorActor parameter

	return ActualDelta != 0;
}


