// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyGameState.h"

AFlappyGameState::AFlappyGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

int32 AFlappyGameState::IncreaseScore()
{
	return ++Score;
}
