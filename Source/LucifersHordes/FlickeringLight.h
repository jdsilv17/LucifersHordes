// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Components/PointLightComponent.h"
#include "FlickeringLight.generated.h"


UCLASS()
class LUCIFERSHORDES_API AFlickeringLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlickeringLight();
	float prevIntensity = 100.0f;
	float randIntensity = 100.0f;
	FColor _lightColor;
	FString _lightColorHex;
	UPointLightComponent* _TorchLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Point Light")
	UPointLightComponent* TorchLight;

	void Flicker();
};
