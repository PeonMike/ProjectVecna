// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PVAICharacter.generated.h"



class UPawnSensingComponent;
class UPVAttributeComponent;
class UUserWidget;
class UPVWorldUserWidget;
class UPVActionComponent;


UCLASS()
class PROJECTVECNA_API APVAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APVAICharacter();

protected:

	UPVWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, category = "Effects")
	FName TimeToHitParamName;

	void SetTargetActor(AActor* NewTarget);

	virtual void PostInitializeComponents() override;


	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UPVAttributeComponent* OwningComp, float NewHealth, float Delta);


	UPROPERTY(VisibleAnywhere, category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPVAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPVActionComponent* ActionComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

};
