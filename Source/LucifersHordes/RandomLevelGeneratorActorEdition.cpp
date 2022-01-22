// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomLevelGeneratorActorEdition.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "GameFramework/PlayerStart.h"
#include "Components/MaterialBillboardComponent.h"
#include "GameFramework/Character.h"
#include "LucifersHordesCharacter.h"

// Sets default values
ARandomLevelGeneratorActorEdition::ARandomLevelGeneratorActorEdition()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!MyBillboard) {
		MyBillboard = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("ICON"));
	}

}

void ARandomLevelGeneratorActorEdition::CreateRooms()
{
	GEngine->AddOnScreenDebugMessage(1, 50, FColor::Purple, TEXT("Creating Rooms"));
	//Create each room
	Rooms.SetNum((int)WorldSize.X * WorldSize.Y * 4);

	FRoom* FirstRoom = new FRoom();
	FirstRoom->position = FVector2D::ZeroVector;
	FirstRoom->roomType = ERoomType::StartRoom;
	Rooms[TwotoOne(WorldSize.X, WorldSize.Y)] = FirstRoom;
	TakenLocations.Add(FVector2D::ZeroVector);
	FVector2D checkPos = FVector2D::ZeroVector;

	//Adjust these numbers to adjust the world gen
	float randomComp = 0.2f, randomCompStart = 0.2f, randomCompEnd = 0.01f;

	for (int i = 0; i < NumOfRooms - 1; i++)
	{
		float randomPercent = ((float)i) / (((float)NumOfRooms - 1));
		randomComp = FMath::Lerp(randomCompStart, randomCompEnd, randomPercent);

		//Get new position
		checkPos = NewPosition();

		if (NumberOfNeighbors(checkPos, TakenLocations) > 1 && FMath::SRand() > randomComp) {
			//Check the new position
			int iter = 0;
			do {
				checkPos = SelectiveNewPosition();
				iter++;
			} while (NumberOfNeighbors(checkPos, TakenLocations) > 1 && iter < 100);
			if (iter >= 50)
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Could not create with fewer neighbors than :" + NumberOfNeighbors(checkPos, TakenLocations)));
		}

		//	//fin position
		FRoom* tempRoom = new FRoom;
		//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Purple, checkPos.ToString());
		tempRoom->position = checkPos;
		//tempRoom.roomType = ERoomType::EMPTY;
		tempRoom->rotation = 0;
		Rooms[TwotoOne(checkPos.X + WorldSize.X, checkPos.Y + WorldSize.Y)] = tempRoom;
		TakenLocations.Add(checkPos);
	}
	GEngine->AddOnScreenDebugMessage(1, 50, FColor::Purple, TEXT("Finsihed Creating rooms"));
}

void ARandomLevelGeneratorActorEdition::SetRoomDoors()
{
	GEngine->AddOnScreenDebugMessage(1, 50, FColor::Purple, TEXT("Adding Doors"));
	for (int x = 0; x < WorldSize.X * 2; x++) {
		for (int y = 0; y < WorldSize.Y * 2; y++) {
			if (Rooms[TwotoOne(x, y)] == nullptr) {
				continue;
			}
			FVector2D gridPos = FVector2D(x, y);
			if (x - 1 < 0) {
				Rooms[TwotoOne(x, y)]->doors.bDoorBottom = false;
			}
			else
			{
				Rooms[TwotoOne(x, y)]->doors.bDoorBottom = (Rooms[TwotoOne(x - 1, y)] != nullptr);
			}
			if (x + 1 >= WorldSize.X * 2) {
				Rooms[TwotoOne(x, y)]->doors.bDoorTop = false;
			}
			else
			{
				Rooms[TwotoOne(x, y)]->doors.bDoorTop = (Rooms[TwotoOne(x + 1, y)] != nullptr);
			}
			if (y - 1 < 0) {
				Rooms[TwotoOne(x, y)]->doors.bDoorLeft = false;
			}
			else
			{
				Rooms[TwotoOne(x, y)]->doors.bDoorLeft = (Rooms[TwotoOne(x, y - 1)] != nullptr);
			}
			if (y + 1 >= WorldSize.Y * 2) {
				Rooms[TwotoOne(x, y)]->doors.bDoorRight = false;
			}
			else
			{
				Rooms[TwotoOne(x, y)]->doors.bDoorRight = (Rooms[TwotoOne(x, y + 1)] != nullptr);
			}
			IdRoom(x, y);
		}
	}
	GEngine->AddOnScreenDebugMessage(1, 50, FColor::Purple, TEXT("Finished Adding Doors"));
}

void ARandomLevelGeneratorActorEdition::SpawnRooms()
{
	//This is going to get really gross really fast.
	GEngine->AddOnScreenDebugMessage(1, 50, FColor::Purple, TEXT("Spawning Rooms"));
	for (int x = 0; x < WorldSize.X * 2; x++) {
		for (int y = 0; y < WorldSize.Y * 2; y++) {
			if (Rooms[TwotoOne(x, y)] == nullptr) {
				continue;
			}
			FString Uniquename = FString::FromInt(x);
			Uniquename.Append(TEXT("-"));
			Uniquename.AppendInt(y);

			int targetLevel = 0;
			switch (Rooms[TwotoOne(x, y)]->roomType)
			{
			case ERoomType::TRoom:
				targetLevel = 0;
				break;
			case ERoomType::CrossRoad:
				targetLevel = 1;
				break;
			case ERoomType::Straight:
				targetLevel = 2;
				break;
			case ERoomType::Turn:
				targetLevel = 3;
				break;
			case ERoomType::End:
				targetLevel = 4;
				break;
			case ERoomType::StartRoom:
				targetLevel = 5;
				break;
			default:
				targetLevel = -1;
				break;
			}

			if (targetLevel >= LevelNames.Num()) {
				GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("ERROR LOADING LEVEL. Did you add a level to slot") + FString::FromInt(targetLevel));
				continue;
			}
			if (targetLevel < 0) {
				GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("ERROR LOADING LEVEL. Target level was out of place ") + FString::FromInt(targetLevel));
				continue;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::FromInt(Rooms[TwotoOne(x, y)]->roomType.GetData()));
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::FromInt(targetLevel));
			ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(this, LevelNames[targetLevel])->CreateInstance(Uniquename);
			if (level == nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("ERROR LOADING LEVEL. Did you add the level to the level view, or did you make a typo? targetLevel was ") + FString::FromInt(targetLevel));
				continue;
			}

			level->bShouldBlockOnLoad = true;
			level->SetShouldBeVisible(true);
			level->SetShouldBeLoaded(true);

			FTransform trans;
			trans.SetComponents(FQuat(FVector::UpVector, FMath::DegreesToRadians(90.0f * Rooms[TwotoOne(x, y)]->rotation)), FVector(x * TileOffset.X, y * TileOffset.Y, 0), FVector::OneVector);
			//newTrans.Set(newPos);
			//newTrans.SetRotation(rotation);
			level->LevelTransform = trans;

		}
	}
	GEngine->AddOnScreenDebugMessage(1, 50, FColor::Purple, TEXT("Finished spawning rooms"));
	return;
}

void ARandomLevelGeneratorActorEdition::SpawnPlayer()
{
	GEngine->AddOnScreenDebugMessage(1, 50, FColor::Purple, TEXT("Spawning Rooms"));
	for (int x = 0; x < WorldSize.X * 2; x++) {
		for (int y = 0; y < WorldSize.Y * 2; y++) {
			if (Rooms[TwotoOne(x, y)] == nullptr) {
				continue;
			}
			if (Rooms[TwotoOne(x, y)]->roomType != ERoomType::StartRoom) {
				continue;
			}
			ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (Player == nullptr) {
				return;
			}
			Player->SetActorLocation(FVector(x * TileOffset.X, y * TileOffset.Y, 200));
			return;
		}
	}

}

void ARandomLevelGeneratorActorEdition::IdRoom(int x, int y)
{
	int roomId = TwotoOne(x, y);
	if (Rooms[roomId]->roomType == ERoomType::StartRoom) {
		return;
	}
	if (CompareDoors(Rooms[roomId]->doors, Cross)) {
		Rooms[roomId]->roomType = ERoomType::CrossRoad;
	}
	else if (CompareDoors(Rooms[roomId]->doors, TurnQ1)) {
		Rooms[roomId]->roomType = ERoomType::Turn;
		Rooms[roomId]->rotation = 0;
	}
	else if (CompareDoors(Rooms[roomId]->doors, TurnQ2)) {
		Rooms[roomId]->roomType = ERoomType::Turn;
		Rooms[roomId]->rotation = 1;
	}
	else if (CompareDoors(Rooms[roomId]->doors, TurnQ3)) {
		Rooms[roomId]->roomType = ERoomType::Turn;
		Rooms[roomId]->rotation = 2;
	}
	else if (CompareDoors(Rooms[roomId]->doors, TurnQ4)) {
		Rooms[roomId]->roomType = ERoomType::Turn;
		Rooms[roomId]->rotation = 3;
	}
	else if (CompareDoors(Rooms[roomId]->doors, PathUp)) {
		Rooms[roomId]->roomType = ERoomType::Straight;
	}
	else if (CompareDoors(Rooms[roomId]->doors, PathRight)) {
		Rooms[roomId]->roomType = ERoomType::Straight;
		Rooms[roomId]->rotation = 1;
	}
	else if (CompareDoors(Rooms[roomId]->doors, EndU)) {
		Rooms[roomId]->roomType = ERoomType::End;
		Rooms[roomId]->rotation = 0;
	}
	else if (CompareDoors(Rooms[roomId]->doors, EndR)) {
		Rooms[roomId]->roomType = ERoomType::End;
		Rooms[roomId]->rotation = 1;
	}
	else if (CompareDoors(Rooms[roomId]->doors, EndD)) {
		Rooms[roomId]->roomType = ERoomType::End;
		Rooms[roomId]->rotation = 2;
	}
	else if (CompareDoors(Rooms[roomId]->doors, EndL)) {
		Rooms[roomId]->roomType = ERoomType::End;
		Rooms[roomId]->rotation = 3;
	}
	else if (CompareDoors(Rooms[roomId]->doors, TJuncND)) {
		Rooms[roomId]->roomType = ERoomType::TRoom;
		Rooms[roomId]->rotation = 0;
	}
	else if (CompareDoors(Rooms[roomId]->doors, TJuncNL)) {
		Rooms[roomId]->roomType = ERoomType::TRoom;
		Rooms[roomId]->rotation = 1;
	}
	else if (CompareDoors(Rooms[roomId]->doors, TJuncNU)) {
		Rooms[roomId]->roomType = ERoomType::TRoom;
		Rooms[roomId]->rotation = 2;
	}
	else if (CompareDoors(Rooms[roomId]->doors, TJuncNR)) {
		Rooms[roomId]->roomType = ERoomType::TRoom;
		Rooms[roomId]->rotation = 3;
	}
}

bool ARandomLevelGeneratorActorEdition::CompareDoors(FDoors door1, FDoors door2) {
	if (door1.bDoorTop != door2.bDoorTop) {
		return false;
	}
	else if (door1.bDoorLeft != door2.bDoorLeft) {
		return false;
	}
	else if (door1.bDoorRight != door2.bDoorRight) {
		return false;
	}
	else if (door1.bDoorBottom != door2.bDoorBottom) {
		return false;
	}
	else {
		return true;
	}
}

int ARandomLevelGeneratorActorEdition::TwotoOne(int x, int y)
{
	return (y * (WorldSize.X * 2)) + x;
}

FVector2D ARandomLevelGeneratorActorEdition::NewPosition()
{
	int x = 0, y = 0;
	FVector2D checkPos = FVector2D::ZeroVector;
	int iter = 0;
	do {
		int index = FMath::RoundToInt(FMath::SRand() * (TakenLocations.Num() - 1));
		x = (int)TakenLocations[index].X;
		y = (int)TakenLocations[index].Y;
		bool UpDown = FMath::RandBool();
		bool pos = FMath::RandBool();

		if (UpDown)
		{
			if (pos)
				y += 1;
			else
				y -= 1;
		}
		else
		{
			if (pos)
				x += 1;
			else
				x -= 1;
		}
		checkPos = FVector2D(x, y);

	} while (TakenLocations.Contains(checkPos) || x >= WorldSize.X || y >= WorldSize.Y || y < -WorldSize.Y || x < -WorldSize.X);
	return checkPos;
}

FVector2D ARandomLevelGeneratorActorEdition::SelectiveNewPosition()
{
	int inc = 0, index = 0;
	int x = 0, y = 0;
	FVector2D checkPos = FVector2D::ZeroVector;
	do {
		inc = 0;
		do {
			index = FMath::RoundToInt(FMath::SRand() * (TakenLocations.Num() - 1));
			inc++;
		} while (NumberOfNeighbors(TakenLocations[index], TakenLocations) > 1 && inc < 100);
		x = (int)TakenLocations[index].X;
		y = (int)TakenLocations[index].Y;
		bool UpDown = FMath::RandBool();
		bool pos = FMath::RandBool();

		if (UpDown)
		{
			if (pos)
				y += 1;
			else
				y -= 1;
		}
		else
		{
			if (pos)
				x += 1;
			else
				x -= 1;
		}
		checkPos = FVector2D(x, y);
	} while (TakenLocations.Contains(checkPos) || x >= WorldSize.X || y >= WorldSize.Y || y < -WorldSize.Y || x < -WorldSize.X);
	if (inc >= 100)
		GEngine->AddOnScreenDebugMessage(20, 5, FColor::Yellow, TEXT("Could not find a location with only 1 neighbor"));
	return checkPos;
}

int ARandomLevelGeneratorActorEdition::NumberOfNeighbors(FVector2D checkPos, TArray<FVector2D> usedLocations)
{
	int neighbors = 0;
	if (usedLocations.Contains(checkPos + FVector2D(0, 1))) {
		neighbors++;
	}
	if (usedLocations.Contains(checkPos + FVector2D(1, 0))) {
		neighbors++;
	}
	if (usedLocations.Contains(checkPos + FVector2D(0, -1))) {
		neighbors++;
	}
	if (usedLocations.Contains(checkPos + FVector2D(-1, 0))) {
		neighbors++;
	}
	return neighbors;
}

// Called when the game starts or when spawned
void ARandomLevelGeneratorActorEdition::BeginPlay()
{
	Super::BeginPlay();
	FMath::RandInit(FMath::Rand());
	//Check to see if there are more rooms requested than can fit inside the grid
	if (NumOfRooms >= (WorldSize.X * WorldSize.Y)) {
		NumOfRooms = FMath::RoundToInt(WorldSize.X * WorldSize.Y);
	}
	CreateRooms();
	SetRoomDoors();
	SpawnRooms();

	SpawnPlayer();

}
