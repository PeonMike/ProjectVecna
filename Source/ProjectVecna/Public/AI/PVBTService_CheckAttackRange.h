// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PVBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVECNA_API UPVBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere, category = "AI")
	FBlackboardKeySelector AttackRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
