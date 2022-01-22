// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "LockingDoor.generated.h"

UCLASS()
class LUCIFERSHORDES_API ALockingDoor : public AActor
{
	GENERATED_BODY()

	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
		FRotator StartRotation;

	UPROPERTY(VisibleAnywhere)
		FRotator TargetRotation;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* LeftDoor;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* RightDoor;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* DoorCollider;

public:	
	// Sets default values for this actor's properties
	ALockingDoor();

	void OpenDoor();
	
	void CloseDoor();

	void LockDoor();

	void UnlockDoor();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		bool bIsLocked;

	UPROPERTY(EditAnywhere)
		bool bRemainUnlocked;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		UAudioComponent* DoorOpenAC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		UAudioComponent* DoorCloseAC;


};
