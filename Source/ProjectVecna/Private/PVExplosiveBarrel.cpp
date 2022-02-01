// Fill out your copyright notice in the Description page of Project Settings.


#include "PVExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APVExplosiveBarrel::APVExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	BaseMesh->SetSimulatePhysics(true);
	// Enabling Simulate physics automatically changes the Profile to PhysicsActor in Blueprint, in C++ we need to change this manually.
	//BaseMesh->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = BaseMesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	RadialForce->SetupAttachment(BaseMesh);

	// Leaving this on applies small constant force via component 'tick' (Optional)
	RadialForce->SetAutoActivate(false);

	RadialForce->Radius = 750.0f;
	RadialForce->ImpulseStrength = 2500.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	RadialForce->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void APVExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void APVExplosiveBarrel::PostInitializeComponents()
{
	// Don't forget to call parent function
	Super::PostInitializeComponents();

	BaseMesh->OnComponentHit.AddDynamic(this, &APVExplosiveBarrel::OnActorHit);
}

void APVExplosiveBarrel::OnActorHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	RadialForce->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive barrel"))

	// %s - string
	// %f - float
	// logs: "OtnerActor: MyActor_1, at gametime: 124.4" 
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombineString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombineString, nullptr, FColor::Green, 2.0f, true);
}

// Called every frame
void APVExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APVExplosiveBarrel::BlowUp()
{
	
}

