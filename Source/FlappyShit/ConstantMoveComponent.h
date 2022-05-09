// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConstantMoveComponent.generated.h"


UCLASS(ClassGroup=(Movement), meta=(BlueprintSpawnableComponent))
class FLAPPYSHIT_API UConstantMoveComponent final : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FVector Movement;

public:
	UPROPERTY(VisibleAnywhere)
	bool bShouldMove = true;
	
	FVector GetMovement() const
	{
		return Movement;
	}

	void SetMovement(const FVector NewMovement)
	{
		Movement = NewMovement;
	}
	
	UConstantMoveComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
