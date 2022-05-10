// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyShitGameModeBase.generated.h"

class APipe;
class AFlappy;
class AFlappyGameState;

UCLASS()
class FLAPPYSHIT_API AFlappyShitGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class APipeSpawnPoint* PipeSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	AActor* PipeDeSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	TArray<APipe*> CurrentPipes;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APipe> PipeClass;

	UPROPERTY(EditAnywhere)
	FVector PipeMovement;

	UPROPERTY(EditDefaultsOnly)
	float SpawnInterval = 2.f;

	UPROPERTY(EditDefaultsOnly)
	float SpawnRandom = 0.2f;

	UPROPERTY(EditDefaultsOnly)
	float ZSpawnRange = 450.f;

	UPROPERTY(VisibleAnywhere)
	AFlappy* Player;

	FTimerHandle SpawnTimer;

	TArray<APipe*> PendingPipes;

	float CurrentZOffSet = 0.f;

public:
	AActor* GetDeSpawnPoint() const
	{
		return PipeDeSpawnPoint;
	}

	void MarkPipeDeSpawn(APipe* Pipe);
	void PlayerDead(AFlappy* Target);
	void IncreaseScore() const;

protected:
	virtual void BeginPlay() override;
	void SpawnPipeTimerDelegate();
	APipe* CreatePipeIfNeeded();

private:
	void SpawnPipe();
	void RandomNextZOffSet();
	void ActivateMainCam() const;

	AFlappyGameState* GetGameState() const;
};
