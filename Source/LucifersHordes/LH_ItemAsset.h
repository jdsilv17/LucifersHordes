// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LH_DataAsset.h"
#include "LH_ItemAsset.generated.h"


/**
 * 
 */
UENUM()
enum class EStatTypes : uint8
{
	None		UMETA(DisplayName = "None"),
	Health		UMETA(DisplayName = "Health"),
	Movespeed	UMETA(DisplayName = "Movement Speed"),
	Defense		UMETA(Displayname = "Defense"),
	Attackspeed	UMETA(Displayname = "Attack Speed"),
	MaxHealth	UMETA(DisplayName = "Max Health"),
	FireRes		UMETA(DisplayName = "Fire Resistance"),
	IceRes		UMETA(DisplayName = "Ice Resistance"),
	PoisonRes	UMETA(DisplayName = "Poison Resistance"),
	StunRes		UMETA(DisplayName = "Stun Resistance"),
	Lifesteal	UMETA(DisplayName = "Lifesteal")
};


UCLASS()
class LUCIFERSHORDES_API ULH_ItemAsset : public ULH_DataAsset
{
	GENERATED_BODY(BlueprintType)
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor")
		TSubclassOf<UObject> Relic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	EStatTypes ItemType;
};
