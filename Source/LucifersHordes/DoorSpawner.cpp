// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorSpawner.h"

// Sets default values
ADoorSpawner::ADoorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	bDoorSpawned = false;

	waitTime = 1.0f;

	numOfEnemiesKilled = 0;
}

void ADoorSpawner::SpawnDoor()
{
	TArray<AActor*> Players;
	UWorld* World = GetWorld();
	UGameplayStatics::GetAllActorsWithTag(World, FName("Player"), Players);

	if (Players.Num() <= 0) {
		return;
	}
	
	AActor* Player = Players[0];

	FTransform PlayerTrans = Player->GetTransform();
	FVector PlayerLoc = PlayerTrans.GetLocation();

	check(GEngine != nullptr)
	if (Door) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		ADoor* newDoor = World->SpawnActor<ADoor>(Door, PlayerLoc, FRotator(0.0f), spawnParams);
		
		if(NextLevel.IsNone())
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Set NextLevel"));
		newDoor->SetTargetWorld(NextLevel);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Set Door in BP"));
	}
}

// Called every frame
void ADoorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (waitTime <= 0) {
		TargetAmount = numOfEnemiesOriginal * percentRequired;
	}
	if (!bDoorSpawned && numOfEnemiesKilled >= TargetAmount && waitTime <= 0) {
		bDoorSpawned = true;
		check(GEngine != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Spawn Door"));

		SpawnDoor();
	}
	else if (!(waitTime <= 0)) {
		waitTime -= DeltaTime;
	}

}

void ADoorSpawner::RemoveEnemy()
{
	numOfEnemiesRemaining--;
	numOfEnemiesKilled++;
}

void ADoorSpawner::AddEnemy()
{
	numOfEnemiesOriginal++;
	numOfEnemiesRemaining++;
}



