// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.h"
#include "LockingDoor.h"
#include "RoomManagerInterface.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "ItemSpawner.h"
#include "EncounterIcon.h"
#include "RoomEncounter.generated.h"

UCLASS()
class LUCIFERSHORDES_API ARoomEncounter : public AActor, public IRoomManagerInterface
{
	GENERATED_BODY()



	USceneComponent* DummyComp;

	FVector RoomSpaceSize;

	bool bMoved;

	class AItemSpawner* ItemSpawner;
public:	
	// Sets default values for this actor's properties
	ARoomEncounter();

	UPROPERTY(EditAnywhere)
		bool bCompleted = false;

	UPROPERTY(EditAnywhere)
		bool bEntered;

	UPROPERTY(EditAnywhere)
		int Target;

	UPROPERTY(EditAnywhere)
		int TotalDead;

	UPROPERTY(EditAnywhere)
		TArray<AEnemySpawnPoint*> enemySpawners;

	UPROPERTY(EditAnywhere)
		TArray<ALockingDoor*> Doors;

	UPROPERTY(EditAnywhere)
		EItemType ItemtoRequest;

	UPROPERTY(EditAnywhere)
		UBoxComponent* EncounterCollision;

	UPROPERTY(EditAnywhere)
		UBoxComponent* RoomSpace;

	UPROPERTY(EditAnywhere)
		USceneComponent* ItemSpawnLocation;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* EncounterSprite;

	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* EncounterMatInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		UAudioComponent* RoomCompleteAC;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int Entered();

	int Spawned_Implementation() override;

	int Died_Implementation() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void FindRoomComponents(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void FinishedEncounter();

private:
	bool started = false;
};
