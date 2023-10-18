// Fill out your copyright notice in the Description page of Project Settings.


#include "PVAnimInstance.h"
#include "GameplayTagContainer.h"
#include "PVActionComponent.h"

void UPVAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AActor* OwningActor = GetOwningActor();

	if (OwningActor)
	{
		ActionComp = Cast<UPVActionComponent>(OwningActor->GetComponentByClass(UPVActionComponent::StaticClass()));
	}
}

void UPVAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	static FGameplayTag StunnedTag = FGameplayTag::RequestGameplayTag("Status. Stunned");

	if (ActionComp)
	{
		bIsStunned = ActionComp->ActiveGameplayTags.HasTag(StunnedTag);
	}

}
