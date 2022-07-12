// Fill out your copyright notice in the Description page of Project Settings.


#include "PVGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/PVAICharacter.h"
#include "PVAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "PVCharacter.h"




static TAutoConsoleVariable<bool> CVarSpawnBot(TEXT("pv.SpawnBots"), true, TEXT("Enable spawning og bots via timer"), ECVF_Cheat);


APVGameModeBase::APVGameModeBase()
{

	SpawnTimerInterval = 2.0f;
}

void APVGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &APVGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void APVGameModeBase::KillAllAI()
{
	for (TActorIterator<APVAICharacter> It(GetWorld()); It; ++It)
	{
		APVAICharacter* Bot = *It;
		UPVAttributeComponent* AttributeComp = UPVAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this);
		}
	}
}


void APVGameModeBase::SpawnBotTimerElapsed()
{

	if (!CVarSpawnBot.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled"));
		return;
	}

	int32 NrOfAliveBots = 0;
	for (TActorIterator<APVAICharacter> It(GetWorld()); It; ++It)
	{
		APVAICharacter* Bot = *It;
		UPVAttributeComponent* AttributeComp = UPVAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots"), NrOfAliveBots);

	float MaxBotCount = 10.0f;
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity. Skipping bot spawn."));
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &APVGameModeBase::OnQueryCompleted);
	}
}

void APVGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper * QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Bot EQS Query Failed"))
		return;
	}




	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}
}

void APVGameModeBase::RespawnPlayerElapsed(AController * Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}


void APVGameModeBase::OnActorKilled(AActor * VictimActor, AActor * Killer)
{
	APVCharacter* Player = Cast<APVCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());


		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}
}
