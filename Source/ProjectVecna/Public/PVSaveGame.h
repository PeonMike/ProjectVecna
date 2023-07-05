// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PVSaveGame.generated.h"



USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

public:

	/* Identifier for which Actor this belongs to */
	UPROPERTY()
	FString ActorName;

	/* For movable Actors, keep location,rotation,scale. */
	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<uint8> ByteData;
};
/**
 * 
 */
UCLASS()
class PROJECTVECNA_API UPVSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:

	UPROPERTY()
	TArray<FActorSaveData> SavedActors;


};
