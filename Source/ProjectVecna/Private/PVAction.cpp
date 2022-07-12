// Fill out your copyright notice in the Description page of Project Settings.


#include "PVAction.h"
#include "PVActionComponent.h"




void UPVAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Start: %s"), *GetNameSafe(this));

	UPVActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunnig = true;
}


void UPVAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stop: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunnig);

	UPVActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunnig = false;
}



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

bool UPVAction::IsRunning() const
{
	return bIsRunnig;
}

UWorld* UPVAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());

	if (Comp)
	{
		return Comp->GetWorld();
	}
	return nullptr;
}



UPVActionComponent* UPVAction::GetOwningComponent() const
{
	return Cast<UPVActionComponent>(GetOuter());
}
