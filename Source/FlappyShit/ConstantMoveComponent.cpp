// Fill out your copyright notice in the Description page of Project Settings.

#include "ConstantMoveComponent.h"

UConstantMoveComponent::UConstantMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UConstantMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bShouldMove && GetOwner())
	{
		const FVector AdjustedMovement = GetMovement() * DeltaTime;
		GetOwner()->AddActorLocalOffset(AdjustedMovement);
	}
}

