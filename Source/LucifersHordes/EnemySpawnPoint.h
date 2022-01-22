// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "RoomManagerInterface.h"
#include "EnemySpawnPoint.generated.h"



USTRUCT()
struct LUCIFERSHORDES_API FEnemyData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorPointer;

	UPROPERTY(EditAnywhere)
		int AmountToSpawn;
};

UCLASS()
class LUCIFERSHORDES_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()



	UPROPERTY()
		UBoxComponent* BoundingBox;

	UPROPERTY()
		bool bSpawned = false;

	UPROPERTY(EditAnywhere, Category = Spawning, Meta = (EditCondition = "!bRandomizeAmount"))
		int EnimiesToSpawn = 1;

	UPROPERTY(EditAnywhere, Category = Spawning)
		bool bRandomizeAmount = true;

	UPROPERTY(EditAnywhere, Category = Spawning, Meta = (EditCondition = "bRandomizeAmount", ClampMin = "1"))
		int MaxEnimiesToSpawn = 1;

	UPROPERTY(EditAnywhere, Category = Spawning, Meta = (EditCondition = "bRandomizeAmount", ClampMin = "1"))
		int MinEnimiesToSpawn = 1;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class ARootEnemyCharacter>> EnemyPool;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AEnemySpawnPoint();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemies();

	UPROPERTY()
		bool bWaitForCommand = true;

	UPROPERTY()
		TScriptInterface<IRoomManagerInterface> RoomPointer;
};
