// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"
#include "UIManagerGameInstance.h"
#include "RootEnemyCharacter.h"

void AEnemySpawnPoint::SpawnEnemies()
{
	if (bSpawned)
		return;
	bSpawned = true;
	FBox boundBox = GetComponentsBoundingBox();
	UWorld* World = GetWorld();
	for (int i = 0; i < EnimiesToSpawn; i++) {


		int enemy = FMath::RandRange(0,EnemyPool.Num() - 1);


		FVector location = FMath::RandPointInBox(boundBox);
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AActor* Enemy = World->SpawnActor<AActor>(EnemyPool[enemy], location, FRotator(0.0f), spawnParams);

		if (ARootEnemyCharacter* rootEnem = Cast<ARootEnemyCharacter>(Enemy))
		{
			if (RoomPointer) {
				rootEnem->RoomPointer = this->RoomPointer;
				rootEnem->notifyRoom();
			}
			
			if (!rootEnem->Tags.Contains("Boss"))
			{
				// set random mesh scale
				float scaleFactor = FMath::RandRange(0.7f, 1.5f);
				rootEnem->GetMesh()->SetWorldScale3D(FVector(scaleFactor));
				// scale health accordingly
				float maxHealth = rootEnem->GetAttributesComponent()->GetMaxHealth();
				rootEnem->GetAttributesComponent()->SetMaxHealth(scaleFactor * maxHealth);
				rootEnem->GetAttributesComponent()->SetCurrentHealth(scaleFactor * maxHealth);
			}

			rootEnem->SetOrigin(GetTransform().GetLocation());
		}
	}

	//this->Destroy();

}

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!BoundingBox) {
		BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundingBox"));
		check(BoundingBox);

		BoundingBox->InitBoxExtent(FVector(100.0f, 100.0f, 5.0f));

		RootComponent = BoundingBox;
	}


}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	/*remainingActors = ActorsToSpawn;
	targetActors = ActorsToSpawn - (ActorsToSpawn * RequiredAmount);*/

	if (!bWaitForCommand) {
		SpawnEnemies();
	}
	else {

		if (MinEnimiesToSpawn > MaxEnimiesToSpawn) {
			MinEnimiesToSpawn = MaxEnimiesToSpawn;
		}

		if (bRandomizeAmount) {
			EnimiesToSpawn = FMath::RandRange(MinEnimiesToSpawn, MaxEnimiesToSpawn);
		}
		if (EnimiesToSpawn <= 0) {
			EnimiesToSpawn = 1;
		}

		//UUIManagerGameInstance* GameInstanceRef = Cast<UUIManagerGameInstance>(GetWorld()->GetGameInstance());

		//EnimiesToSpawn += 2;
			//(GameInstanceRef->currLevelsCleared * GameInstanceRef->completedRuns);
	}

}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (!bTargetReached && targetActors > remainingActors) {
		bTargetReached = true;
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, TEXT("Target Reached. Spawn Door"));
	}*/
}

