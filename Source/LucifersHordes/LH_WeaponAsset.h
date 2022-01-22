// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LH_DataAsset.h"
#include "LH_WeaponAsset.generated.h"

/**
 * 
 */

class UCapsuleComponent;
class UParticleSystemComponent;
class USoundCue;
class UAudioComponent;

UCLASS(BlueprintType)
class LUCIFERSHORDES_API ULH_WeaponAsset : public ULH_DataAsset
{
	GENERATED_BODY()

public:

	ULH_WeaponAsset() : AMeleeWeapon(nullptr) {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor")
		TSubclassOf<AActor> AMeleeWeapon;
};
