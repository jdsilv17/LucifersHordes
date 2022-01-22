// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DrawDebugHelpers.h"
#include "LH_GameplayStatics.h"

#include "EnvironmentalEffects.generated.h"

UENUM()
enum class EVHType : uint8
{
	BottomlessPit	UMETA(DisplayName = "Bottomless Pit"), 
	WindFunnel		UMETA(DisplayName = "Wind Funnel"), 
	Thistle			UMETA(DisplayName = "Thistle"), 
	IceFloor		UMETA(DisplayName = "Ice Floor"), 
	TarPool			UMETA(DisplayName = "Tar Pool"), 
	LavaFloor		UMETA(DisplayName = "Lava Floor"), 
	ToxicPool		UMETA(DisplayName = "Toxic Pool")
};

UCLASS()
class LUCIFERSHORDES_API AEnvironmentalEffects : public ATriggerBox
{
	GENERATED_BODY()
public:
	
	AEnvironmentalEffects();
	AEnvironmentalEffects(EVHType hazard, int effectMod);

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVH")
		float EffectModifier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVH")
		EVHType Hazard = EVHType::BottomlessPit;


private:
	float Effect = 1;
	FVector RandomXYVector(float min, float max);
	TArray<EDamageTypes> thistleDT;
};
