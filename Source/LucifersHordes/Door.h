// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Unreal
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

//Lucy

#include "UIManagerGameInstance.h"
#include "Door.generated.h"

UCLASS()
class LUCIFERSHORDES_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditInstanceOnly)
		FName TargetWorldName;

	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent* BoxCollider;

	float delay;

	bool bReady;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);

	void DoorOpened();

	void SetTargetWorld(FName newName);
};
