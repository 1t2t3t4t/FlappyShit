// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlappyController.generated.h"

UCLASS()
class FLAPPYSHIT_API AFlappyController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlappyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
