// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestClassForRoom.generated.h"

//#define TRoom = 0
//#define CrossRoad = 1
//#define Straight = 2
//#define Turn = 3
//#define End = 4

//enum RoomTypes
//{
//	TRoom = 0			,
//	CrossRoad = 1		,
//	Straight = 2		,
//	Turn = 3			,
//	End = 4				,
//	EMPTY = 10			,
//};
UENUM()
enum class ERoomType : uint8
{
		TRoom = 0			,
		CrossRoad = 1		,
		Straight = 2		,
		Turn = 3			,
		End = 4				,
		StartRoom,
		BossRoom,
		EMPTY = 10			,
};

USTRUCT()
struct FDoors
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		bool bDoorTop = false;

	UPROPERTY(EditAnywhere)
		bool bDoorRight = false;

	UPROPERTY(EditAnywhere)
		bool bDoorBottom = false;

	UPROPERTY(EditAnywhere)
		bool bDoorLeft = false;
};

USTRUCT()
struct LUCIFERSHORDES_API FRoom
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
		FVector2D position;
	UPROPERTY(VisibleAnywhere)
		ERoomType roomType;
	UPROPERTY(VisibleAnywhere)
		FDoors doors;
	UPROPERTY(VisibleAnywhere)
		int rotation = 0;
};
