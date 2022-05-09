// Fill out your copyright notice in the Description page of Project Settings.


#include "Pipe.h"

#include "ConstantMoveComponent.h"
#include "FlappyShitGameModeBase.h"
#include "Components/BoxComponent.h"


FName APipe::Tag = TEXT("Pipe");

// Sets default values
APipe::APipe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.2f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	UpperBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Upper Box Component"));
	UpperBoxComponent->SetupAttachment(RootComponent);

	UpperStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Upper Static Mesh"));
	UpperStaticMeshComponent->SetupAttachment(UpperBoxComponent);

	LowerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Lower Component"));
	LowerBoxComponent->SetupAttachment(RootComponent);

	LowerStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lower Static Mesh"));
	LowerStaticMeshComponent->SetupAttachment(LowerBoxComponent);

	MoveComponent = CreateDefaultSubobject<UConstantMoveComponent>(TEXT("Constant Move Component"));

	ScoreTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Score Trigger"));
	ScoreTrigger->SetupAttachment(RootComponent);

	Tags.Push(Tag);
}

// Called when the game starts or when spawned
void APipe::BeginPlay()
{
	Super::BeginPlay();
	MoveComponent->SetMovement(Movement);
	ScoreTrigger->OnComponentEndOverlap.AddDynamic(this, &APipe::ScoreTriggerOnLeave);
}

void APipe::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	if (AFlappyShitGameModeBase* GameModeOwner = Cast<AFlappyShitGameModeBase>(NewOwner))
	{
		GameMode = GameModeOwner;
	}
}

// Called every frame
void APipe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (const AActor* DeSpawnPoint = GameMode->GetDeSpawnPoint())
	{
		if (GetActorLocation().X <= DeSpawnPoint->GetActorLocation().X)
		{
			GameMode->MarkPipeDeSpawn(this);
		}
	}
}

void APipe::ScoreTriggerOnLeave(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag(TEXT("Player")))
		{
 			UE_LOG(LogTemp, Warning, TEXT("Got Poiunt"));
		}
	}
}

void APipe::SetMovement(const FVector NewMovement)
{
	Movement = NewMovement;
	MoveComponent->SetMovement(NewMovement);
}
