// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestClassForRoom.h"
#include "Room.h"
#include "RandomLevelGeneratorActorEdition.generated.h"

UCLASS()
class LUCIFERSHORDES_API ARandomLevelGeneratorActorEdition : public AActor
{
	GENERATED_BODY()

	void CreateRooms();
	void SetRoomDoors();
	void SpawnRooms();
	void SpawnPlayer();

	//Helpers

	//Id the room type
	void IdRoom(int x, int y);

	bool CompareDoors(FDoors door1, FDoors door2);

	//2D to 1D array
	int TwotoOne(int x, int y);

	//Get a new Room pos
	FVector2D NewPosition();

	//Be pickier
	FVector2D SelectiveNewPosition();

	//Find how many neighbors a room has
	int NumberOfNeighbors(FVector2D checkPos, TArray<FVector2D> usedLocations);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialBillboardComponent* MyBillboard;

	UPROPERTY(EditAnywhere)
		TArray<FName> LevelNames;

	UPROPERTY(EditAnywhere)
		TArray<FVector2D> TakenLocations;

	UPROPERTY(EditAnywhere)
		FVector2D WorldSize;

	UPROPERTY(EditAnywhere)
		FVector2D TileOffset;

	UPROPERTY(EditANywhere)
		int NumOfRooms;

	//UPROPERTY(VisibleAnywhere)
	TArray<FRoom*> Rooms;

public:

	// Sets default values for this actor's properties
	ARandomLevelGeneratorActorEdition();

private:
	//Definitions for roomtypes
#pragma region Roomtypes
	FDoors PathUp = {
		true,
		false,
		true,
		false
	};
	FDoors PathRight = {
		false,
		true,
		false,
		true,
	};
	FDoors TurnQ1 = {
		true,
		true,
		false,
		false,
	};
	FDoors TurnQ2 = {
		false,
		true,
		true,
		false,
	};
	FDoors TurnQ3 = {
		false,
		false,
		true,
		true,
	};
	FDoors TurnQ4 = {
		true,
		false,
		false,
		true,
	};
	FDoors EndU = {
		true,
		false,
		false,
		false,
	};
	FDoors EndR = {
		false,
		true,
		false,
		false,
	};
	FDoors EndD = {
		false,
		false,
		true,
		false,
	};
	FDoors EndL = {
		false,
		false,
		false,
		true,
	};
	FDoors Cross = {
		true,
		true,
		true,
		true,
	};
	FDoors TJuncNL = {
		true,
		true,
		true,
		false,
	};
	FDoors TJuncND = {
		true,
		true,
		false,
		true,
	};
	FDoors TJuncNR = {
		true,
		false,
		true,
		true,
	};
	FDoors TJuncNU = {
		false,
		true,
		true,
		true,
	};
#pragma endregion
};
