// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PVAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"


void APVAIController::BeginPlay()
{
	Super::BeginPlay();


	if (ensureMsgf(BehaviorTree, TEXT("Behavoir tree is nullptr! Please assign BT in your AI controller")))
	{
		RunBehaviorTree(BehaviorTree);
	}


	/*
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());

		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
	*/
}
