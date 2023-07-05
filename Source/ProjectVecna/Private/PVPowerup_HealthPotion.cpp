// Fill out your copyright notice in the Description page of Project Settings.


#include "PVPowerup_HealthPotion.h"
#include "PVAttributeComponent.h"

void APVPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UPVAttributeComponent* AttributeComp = Cast<UPVAttributeComponent>(InstigatorPawn->GetComponentByClass(UPVAttributeComponent::StaticClass()));
	// Check if not already at max health
	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		// Only activate if healed successfully
		if (AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
		{
			HideAndCooldownPowerup();
		}
	}
}

APVPowerup_HealthPotion::APVPowerup_HealthPotion()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// Disable collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}
