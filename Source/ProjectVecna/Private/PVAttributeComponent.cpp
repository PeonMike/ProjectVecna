// Fill out your copyright notice in the Description page of Project Settings.


#include "PVAttributeComponent.h"
#include "PVGameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "PVSaveGame.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("pv.DamageMultiplier"), 1.0f, TEXT("Multiply Damage"), ECVF_Cheat);



// Sets default values for this component's properties
UPVAttributeComponent::UPVAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;
	StaticChargeMax = 100;
	StaticCharge = 0;

	SetIsReplicatedByDefault(true);
}




bool UPVAttributeComponent::Kill(AActor* InstigatorActor)
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
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}


	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	ApplyStaticChargeChange(InstigatorActor, Delta);

	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	float ActualDelta = NewHealth - OldHealth;

	//Is Server?
	if (GetOwner()->HasAuthority())
	{
		Health = NewHealth;

		if (ActualDelta != 0.0f)
		{
			MultiCastHealthChanged(InstigatorActor, Health, ActualDelta);
		}

		// isDead?
		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			APVGameModeBase* GM = GetWorld()->GetAuthGameMode<APVGameModeBase>();

			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}

	return ActualDelta != 0;
}

bool UPVAttributeComponent::ApplyStaticChargeChange(AActor * InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}


	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	float OldCharge = StaticCharge;
	float NewCharge = FMath::Clamp(StaticCharge - Delta + 7, 0.0f, StaticChargeMax);
	float ActualDelta = NewCharge + OldCharge;

	//Is Server?
	if (GetOwner()->HasAuthority())
	{
		StaticCharge = NewCharge;

		if (ActualDelta != 0.0f)
		{
			MultiCastStaticChargeChanged(InstigatorActor, StaticCharge, ActualDelta);
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



bool UPVAttributeComponent::IsActorAlive(AActor* Actor)
{
	UPVAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}


void UPVAttributeComponent::MultiCastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

void UPVAttributeComponent::MultiCastStaticChargeChanged_Implementation(AActor* InstigatorActor, float NewCharge, float Delta)
{
	OnStaticChargeChanged.Broadcast(InstigatorActor, this, NewCharge, Delta);
}


void UPVAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPVAttributeComponent, Health);
	DOREPLIFETIME(UPVAttributeComponent, HealthMax);
	DOREPLIFETIME(UPVAttributeComponent, StaticCharge);
	DOREPLIFETIME(UPVAttributeComponent, StaticChargeMax);

}

