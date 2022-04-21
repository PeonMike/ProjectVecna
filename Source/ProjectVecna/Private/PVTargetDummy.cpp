// Fill out your copyright notice in the Description page of Project Settings.


#include "PVTargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "PVAttributeComponent.h"

// Sets default values
APVTargetDummy::APVTargetDummy()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateAbstractDefaultSubobject<UPVAttributeComponent>("AttributeComp");
	// Trigger when health is changed
	AttributeComp->OnHealthChanged.AddDynamic(this, &APVTargetDummy::OnHealthChanged);

}

void APVTargetDummy::OnHealthChanged(AActor * InstigatorActor, UPVAttributeComponent * OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);

	}
}