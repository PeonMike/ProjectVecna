// Fill out your copyright notice in the Description page of Project Settings.


#include "PVItemChest.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APVItemChest::APVItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);


	TargetPitch = 120;

	SetReplicates(true);

}


// Called when the game starts or when spawned
void APVItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}


void APVItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	//

	bLidOpened = !bLidOpened;
	OnRep_LidOpened();
}

void APVItemChest::OnActorLoaded_Implementation()
{
	OnRep_LidOpened();
}

void APVItemChest::OnRep_LidOpened()
{
	float CurrPitch = bLidOpened ? TargetPitch : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(CurrPitch, 0, 0));
}


void APVItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APVItemChest, bLidOpened);
}

