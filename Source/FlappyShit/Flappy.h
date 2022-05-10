// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Flappy.generated.h"

class AFlappyShitGameModeBase;

UCLASS()
class FLAPPYSHIT_API AFlappy : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	float JumpForce = 100.f;

	UPROPERTY(VisibleAnywhere)
	bool bIsDead = false;
	
public:
	// Sets default values for this pawn's properties
	AFlappy();

	bool GetIsDead() const
	{
		return bIsDead;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Jump();

private:
	UFUNCTION()
	void OnHitComponent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    FVector NormalImpulse, const FHitResult& Hit);
	AFlappyShitGameModeBase* GetGameMode() const;
};
