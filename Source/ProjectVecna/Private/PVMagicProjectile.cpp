// Fill out your copyright notice in the Description page of Project Settings.


#include "PVMagicProjectile.h"
#include "PVAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "PVGameplayFunctionLibrary.h"
#include "PVActionComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PVActionEffect.h"
#include "PVCharacter.h"


// Sets default values
APVMagicProjectile::APVMagicProjectile()
{
 
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APVMagicProjectile::OnActorOverlap);

	DamageAmount = 20.0f;
}

void APVMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator()) 
	{
		/*
		AActor* MyActor = GetInstigator();

		FVector DistanceDif = MyActor->GetActorLocation() - OtherActor->GetActorLocation();

		DistanceDif.Normalize();
		float DotProduct = OtherActor->GetActorForwardVector() | DistanceDif;

		if (DotProduct < -0.5f) {
			DamageAmount = 100.0f;
		}
		*/
		//static FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Status.Parrying");

		UPVActionComponent* ActionComp = Cast<UPVActionComponent>(OtherActor->GetComponentByClass(UPVActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MoveComp->Velocity = -MoveComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		if (UPVGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();

			if (ActionComp && HasAuthority())
			{
				ActionComp->AddAction(GetInstigator(), BurningActionClass);
			}
		}
	}
}
