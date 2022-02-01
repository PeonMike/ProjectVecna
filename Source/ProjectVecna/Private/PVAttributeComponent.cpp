// Fill out your copyright notice in the Description page of Project Settings.


#include "PVAttributeComponent.h"

// Sets default values for this component's properties
UPVAttributeComponent::UPVAttributeComponent()
{
	Health = 100;
}



bool UPVAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}


