// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PVTargetDummy.generated.h"

class UPVAttributeComponent;

UCLASS()
class PROJECTVECNA_API APVTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	

	APVTargetDummy();

protected:

	UPROPERTY(VisibleAnywhere)
	UPVAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UPVAttributeComponent* OwningComp, float NewHealth, float Delta);



};
