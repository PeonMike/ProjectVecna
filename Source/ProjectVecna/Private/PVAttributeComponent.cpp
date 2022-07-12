// Fill out your copyright notice in the Description page of Project Settings.


#include "PVAttributeComponent.h"
#include "PVGameModeBase.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("pv.DamageMultiplier"), 1.0f, TEXT("Multiply Damage"), ECVF_Cheat);



// Sets default values for this component's properties
UPVAttributeComponent::UPVAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;
}



bool UPVAttributeComponent::Kill(AActor * InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
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



bool UPVAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	float OldHealth = Health;


	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta); // @fixme: Still nullptr for InstigatorActor parameter

	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		APVGameModeBase* GM = GetWorld()->GetAuthGameMode<APVGameModeBase>();

		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDelta != 0;
}


UPVAttributeComponent* UPVAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UPVAttributeComponent>(FromActor->GetComponentByClass(UPVAttributeComponent::StaticClass()));
	}

	return nullptr;
}



bool UPVAttributeComponent::IsActorAlive(AActor * Actor)
{
	UPVAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}