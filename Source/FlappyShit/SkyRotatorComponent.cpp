// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyRotatorComponent.h"

USkyRotatorComponent::USkyRotatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USkyRotatorComponent::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}

void USkyRotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (StaticMeshComponent)
	{
		StaticMeshComponent->AddLocalRotation(RotatingSpeed * DeltaTime);
	}
}

