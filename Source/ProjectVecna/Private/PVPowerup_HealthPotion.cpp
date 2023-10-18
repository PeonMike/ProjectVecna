// Fill out your copyright notice in the Description page of Project Settings.


#include "PVPowerup_HealthPotion.h"
#include "PVAttributeComponent.h"


#define LOCTEXT_NAMESPACE "InteractableActors"

void APVPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UPVAttributeComponent* AttributeComp = UPVAttributeComponent::GetAttributes(InstigatorPawn);
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


FText APVPowerup_HealthPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	//UPVAttributeComponent* AttributeComp = Cast<UPVAttributeComponent>(InstigatorPawn->GetComponentByClass(UPVAttributeComponent::StaticClass()));
	UPVAttributeComponent* AttributeComp = UPVAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp && AttributeComp->IsFullHealth())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at Full health.");
	}

	return LOCTEXT("HealthPotion_InteractMessage", "Costs you liver. Restore health to full.");

}

APVPowerup_HealthPotion::APVPowerup_HealthPotion()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// Disable collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}


#undef LOCTEXT_NAMESPACE