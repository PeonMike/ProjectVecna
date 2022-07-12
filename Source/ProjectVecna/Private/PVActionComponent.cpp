// Fill out your copyright notice in the Description page of Project Settings.


#include "PVActionComponent.h"
#include "PVAction.h"


UPVActionComponent::UPVActionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
}


void UPVActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UPVAction> ActionClass : DefaultAction)
	{
		AddAction(ActionClass);
	}

	
}

void UPVActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);
}


void UPVActionComponent::AddAction(TSubclassOf<UPVAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UPVAction* NewAction = NewObject<UPVAction>(this, ActionClass);

	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}

}


bool UPVActionComponent::StartActionByName(AActor * Instigator, FName ActionName)
{
	for (UPVAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{

				continue;
			}

			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UPVActionComponent::StopActionByName(AActor * Instigator, FName ActionName)
{
	for (UPVAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}

		}
	}
	return false;
}
