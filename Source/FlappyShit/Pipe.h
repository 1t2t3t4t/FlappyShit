// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pipe.generated.h"

UCLASS()
class FLAPPYSHIT_API APipe : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* UpperBoxComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* UpperStaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* LowerBoxComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LowerStaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	class UConstantMoveComponent* MoveComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ScoreTrigger;

	UPROPERTY(EditDefaultsOnly)
	FVector Movement;

	UPROPERTY(VisibleAnywhere)
	class AFlappyShitGameModeBase* GameMode;
	
public:
	static FName Tag;
	
	APipe();

	void SetMovement(const FVector NewMovement);

	UConstantMoveComponent* GetMoveComponent() const
	{
		return MoveComponent;
	}

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetOwner(AActor* NewOwner) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ScoreTriggerOnLeave(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
