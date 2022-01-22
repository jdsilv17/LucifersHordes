// Fill out your copyright notice in the Description page of Project Settings.


#include "FlickeringLight.h"

// Sets default values
AFlickeringLight::AFlickeringLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TorchLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	_lightColorHex = "FFA331FF";
	TorchLight->LightColor = _lightColor.FromHex(_lightColorHex);
	TorchLight->Intensity = 400;
	TorchLight->AttenuationRadius = 800;
	TorchLight->SetVisibleFlag(true);
	TorchLight->SetMobility(EComponentMobility::Movable);
	_TorchLight = TorchLight;
	RootComponent = _TorchLight;
}

// Called when the game starts or when spawned
void AFlickeringLight::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFlickeringLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Flicker();
}

void AFlickeringLight::Flicker()
{
	prevIntensity = randIntensity;
	randIntensity = FMath::FRandRange(100, 800);
	float lerpedIntensity = FMath::Lerp(prevIntensity, randIntensity, 0.5f);
	_TorchLight->SetIntensity(lerpedIntensity);
}

