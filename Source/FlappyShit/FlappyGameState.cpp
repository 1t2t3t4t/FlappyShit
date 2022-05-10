// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyGameState.h"

AFlappyGameState::AFlappyGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFlappyGameState::IncreaseScore()
{
	Score++;
}
