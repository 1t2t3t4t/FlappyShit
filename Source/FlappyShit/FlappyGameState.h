// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FlappyGameState.generated.h"

UCLASS()
class FLAPPYSHIT_API AFlappyGameState : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	int32 Score = 0;
	
public:
	AFlappyGameState();

	int32 GetScore() const
	{
		return Score;
	}
	
	void IncreaseScore();
};
