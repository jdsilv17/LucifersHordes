// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Door.h"
#include "DoorSpawner.generated.h"

UCLASS()
class LUCIFERSHORDES_API ADoorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawning)
		int numOfEnemiesOriginal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawning)
		int numOfEnemiesRemaining;

	UPROPERTY(EditInstanceOnly, Category = Spawning)
		FName NextLevel;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Spawning, meta = (ClampMax = "1", ClampMin = "0"))
		float percentRequired;

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
		TSubclassOf<ADoor> Door;

	UPROPERTY(VisibleInstanceOnly)
		bool bDoorSpawned;

	UPROPERTY(VisibleInstanceOnly)
		float waitTime;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawning)
		int TargetAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawning)
		int numOfEnemiesKilled;

	void SpawnDoor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RemoveEnemy();

	void AddEnemy();

};
