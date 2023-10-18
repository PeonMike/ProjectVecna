// Fill out your copyright notice in the Description page of Project Settings.


#include "PVAction.h"
#include "PVActionComponent.h"
#include "../ProjectVecna.h"
#include "Net/UnrealNetwork.h"



bool UPVAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	UPVActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}


void UPVAction::Initialize(UPVActionComponent * NewActionComp)
{
	ActionComp = NewActionComp;
}


void UPVAction::StartAction_Implementation(AActor* Instigator)
{

	UPVActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;

	if (GetOwningComponent()->GetOwnerRole() == ROLE_Authority)
	{
		TimeStarted = GetWorld()->TimeSeconds;
	}

	GetOwningComponent()->OnActionStarted.Broadcast(GetOwningComponent(), this);
}


void UPVAction::StopAction_Implementation(AActor* Instigator)
{

	//ensureAlways(RepData.bIsRunning);

	UPVActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	RepData.bIsRunning = false;
	RepData.Instigator = Instigator;

	GetOwningComponent()->OnActionStopped.Broadcast(GetOwningComponent(), this);
}


UWorld* UPVAction::GetWorld() const
{
	AActor* Actor = Cast<AActor>(GetOuter());

	if (Actor)
	{
		return Actor->GetWorld();
	}
	return nullptr;
}


void UPVAction::OnRep_RepData()
{
	if (RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StartAction(RepData.Instigator);
	}
}


bool UPVAction::IsRunning() const
{
	return RepData.bIsRunning;
}




UPVActionComponent* UPVAction::GetOwningComponent() const
{
	return ActionComp;
}


void UPVAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPVAction, RepData);
	DOREPLIFETIME(UPVAction, TimeStarted);
	DOREPLIFETIME(UPVAction, ActionComp);
}