// Fill out your copyright notice in the Description page of Project Settings.


#include "Flappy.h"

#include "Pipe.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AFlappy::AFlappy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetSimulatePhysics(true);
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void AFlappy::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentHit.AddDynamic(this, &AFlappy::OnHitComponent);
}

// Called every frame
void AFlappy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFlappy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AFlappy::Jump);
}

void AFlappy::Jump()
{
	const FVector JumpForceVec = GetActorUpVector() * JumpForce;
	SphereComponent->AddImpulse(JumpForceVec);
}

void AFlappy::OnHitComponent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             FVector NormalImpulse, const FHitResult& Hit)
{
 	if (OtherActor && OtherActor->ActorHasTag(APipe::Tag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Dead"));
	}
}
