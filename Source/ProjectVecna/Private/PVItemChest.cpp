// Fill out your copyright notice in the Description page of Project Settings.


#include "PVItemChest.h"
#include "Components/StaticMeshComponent.h"

void APVItemChest::Interact_Implementation(APawn * InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

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

}

// Called when the game starts or when spawned
void APVItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APVItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

