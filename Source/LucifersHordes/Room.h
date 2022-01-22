// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

//UENUM()
//enum class ERoomType : uint8
//{
//	TRoom = 0,
//	CrossRoad = 1,
//	Straight = 2,
//	Turn = 3,
//	End = 4,
//	StartRoom,
//	EMPTY = 10,
//};

UCLASS()
class LUCIFERSHORDES_API ABoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoom();

	UPROPERTY(VisibleAnywhere)
		FVector2D position;
	/*UPROPERTY(VisibleAnywhere)
		ERoomType roomType;*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
