// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyShitGameModeBase.h"

#include "DrawDebugHelpers.h"
#include "Flappy.h"
#include "FlappyController.h"
#include "FlappyGameState.h"
#include "Pipe.h"
#include "PipeSpawnPoint.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AFlappyShitGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ActivateMainCam();
	AActor* Actor = UGameplayStatics::GetActorOfClass(this, APipeSpawnPoint::StaticClass());
	if (APipeSpawnPoint* Point = Cast<APipeSpawnPoint>(Actor))
	{
		PipeSpawnPoint = Point;
	}
	TArray<AActor*> DeSpawnPoints;
	UGameplayStatics::GetAllActorsWithTag(this, TEXT("DespawnPoint"), DeSpawnPoints);
	if (DeSpawnPoints.Num() > 0)
	{
		PipeDeSpawnPoint = DeSpawnPoints[0];
	}
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AFlappyShitGameModeBase::SpawnPipeTimerDelegate, SpawnInterval, false);

	DrawDebugSphere(GetWorld(), FVector(0, 0, -ZSpawnRange), 20.f, 6, FColor::Red, true);
	DrawDebugSphere(GetWorld(), FVector(0, 0, ZSpawnRange), 20.f, 6, FColor::Red, true);

	Player = Cast<AFlappy>(UGameplayStatics::GetActorOfClass(this, AFlappy::StaticClass()));
}

void AFlappyShitGameModeBase::SpawnPipeTimerDelegate()
{
	SpawnPipe();
	SpawnTimer.Invalidate();
	const float Rand = FMath::RandRange(-SpawnRandom, SpawnRandom);
	const float SpawnRate = FMath::Max(SpawnInterval + Rand, 0.1f);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AFlappyShitGameModeBase::SpawnPipeTimerDelegate, SpawnRate, false);
}

APipe* AFlappyShitGameModeBase::CreatePipeIfNeeded()
{
	if (PendingPipes.Num() > 0)
	{
		return PendingPipes.Pop();
	}

	APipe* NewPipe = GetWorld()->SpawnActor<APipe>(PipeClass, PipeSpawnPoint->GetActorLocation(), FRotator::ZeroRotator);
	NewPipe->SetMovement(PipeMovement);
	NewPipe->SetOwner(this);
	return NewPipe;
}

void AFlappyShitGameModeBase::SpawnPipe()
{
	if (PipeSpawnPoint)
	{
		RandomNextZOffSet();
		FVector SpawnPoint = PipeSpawnPoint->GetActorLocation();
		SpawnPoint.Z = CurrentZOffSet;
		APipe* Pipe = CreatePipeIfNeeded();
		Pipe->SetActorLocation(SpawnPoint);
		CurrentPipes.AddUnique(Pipe);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Pipe Spawn Point!!"));
	}
}

void AFlappyShitGameModeBase::RandomNextZOffSet()
{
	CurrentZOffSet = FMath::PerlinNoise1D(GetWorld()->GetTimeSeconds()) * ZSpawnRange;
}

void AFlappyShitGameModeBase::ActivateMainCam() const
{
	TArray<AActor*> Result;
	UGameplayStatics::GetAllActorsWithTag(this, TEXT("MainCam"), Result);
	if (Result.Num() > 0)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (ACameraActor* CameraActor = Cast<ACameraActor>(Result[0]))
		{
			PlayerController->SetViewTarget(CameraActor);
		}
	}
}

AFlappyGameState* AFlappyShitGameModeBase::GetGameState() const
{
	return Cast<AFlappyGameState>(GameState);
}

void AFlappyShitGameModeBase::MarkPipeDeSpawn(APipe* Pipe)
{
	CurrentPipes.Remove(Pipe);
	PendingPipes.AddUnique(Pipe);
}

void AFlappyShitGameModeBase::PlayerDead(AFlappy* Target)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		Target->DisableInput(PlayerController);
	}
}

void AFlappyShitGameModeBase::IncreaseScore() const
{
	if (Player && !Player->GetIsDead())
	{
		if (AFlappyGameState* FlappyGameState = GetGameState())
		{
			const int32 Score = FlappyGameState->IncreaseScore();
			if (const AFlappyController* PlayerController = Cast<AFlappyController>(GetWorld()->GetFirstPlayerController()))
			{
				PlayerController->IncreasePlayerScore(Score);
			}
		}
	}
}
