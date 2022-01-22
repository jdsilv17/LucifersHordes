// Fill out your copyright notice in the Description page of Project Settings.


#include "LockingDoor.h"

// Sets default values
ALockingDoor::ALockingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComp) {
		RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
		RootComponent = RootComp;
	}

	if (!LeftDoor) {
		LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
		LeftDoor->SetupAttachment(RootComponent);
	}
	if (!RightDoor) {
		RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
		RightDoor->SetupAttachment(RootComponent);
	}

	if (!DoorCollider) {
		DoorCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollider"));
		DoorCollider->SetupAttachment(RootComponent);
		this->DoorCollider->OnComponentBeginOverlap.AddDynamic(this, &ALockingDoor::OnOverlapBegin);
	}
	if (!DoorOpenAC) {
		DoorOpenAC = CreateDefaultSubobject<UAudioComponent>(TEXT("OpenAC"));
		DoorOpenAC->SetupAttachment(RootComponent);
	}
	if (!DoorCloseAC) {
		DoorCloseAC = CreateDefaultSubobject<UAudioComponent>(TEXT("CloseAC"));
		DoorCloseAC->SetupAttachment(RootComponent);
	}

	bIsLocked = false;
	bRemainUnlocked = false;
}

void ALockingDoor::OpenDoor()
{
	if (DoorOpenAC)
		DoorOpenAC->Play(0.0f);
	if (LeftDoor->GetRelativeRotation().GetManhattanDistance(TargetRotation) > 1.0f
		&& RightDoor->GetRelativeRotation().GetManhattanDistance(TargetRotation.GetInverse()) > 1.0f
		)
	{
		LeftDoor->SetRelativeRotation(FMath::Lerp(TargetRotation, LeftDoor->GetRelativeRotation(), 0.8f));
		RightDoor->SetRelativeRotation(FMath::Lerp(TargetRotation.GetInverse(), RightDoor->GetRelativeRotation(), 0.8f));
	}
}

void ALockingDoor::CloseDoor()
{
	if (DoorCloseAC)
		DoorCloseAC->Play(0.0f);
	if (LeftDoor->GetRelativeRotation().GetManhattanDistance(StartRotation) > 1.0f
		&& RightDoor->GetRelativeRotation().GetManhattanDistance(StartRotation) > 1.0f
		)
	{
		LeftDoor->SetRelativeRotation(FMath::Lerp(StartRotation, LeftDoor->GetRelativeRotation(), 0.8f));
		RightDoor->SetRelativeRotation(FMath::Lerp(StartRotation, RightDoor->GetRelativeRotation(), 0.8f));
	}
}

void ALockingDoor::LockDoor()
{
	bIsLocked = true;
}

void ALockingDoor::UnlockDoor()
{
	bIsLocked = false;
}

void ALockingDoor::OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (OtherActor->ActorHasTag("Player") && !bIsLocked)
		{
			bRemainUnlocked = true;
		}
	}
}

// Called when the game starts or when spawned
void ALockingDoor::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = FRotator::ZeroRotator;

	TargetRotation = FRotator(0, 135, 0);

	bIsLocked = false;
	bRemainUnlocked = false;
}

// Called every frame
void ALockingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if unlocked and should remain so
	if (bRemainUnlocked && !bIsLocked)
	{
		SetActorEnableCollision(false);
		OpenDoor();
	}
	else if (bIsLocked || (!bRemainUnlocked && !bIsLocked))
	{
		CloseDoor();
		SetActorEnableCollision(true);
	}
}


