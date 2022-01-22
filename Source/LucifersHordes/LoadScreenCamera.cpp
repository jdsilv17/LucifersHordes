// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadScreenCamera.h"

// Sets default values
ALoadScreenCamera::ALoadScreenCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	startPos.X = 0.0f;
	startPos.Z = 1430.0f;
	startPos.Y = -400.0f;

	endPos.X = 0.0f;
	endPos.Z = 600.0f;
	endPos.Y = 1160.0f;

	moveSpeed = 0.5;

	currPos = startPos;
}

// Called when the game starts or when spawned
void ALoadScreenCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALoadScreenCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currPos = FMath::VInterpTo(currPos, endPos, DeltaTime, moveSpeed);
	this->SetActorLocation(currPos);
}

