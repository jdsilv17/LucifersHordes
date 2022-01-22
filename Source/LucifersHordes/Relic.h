// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LH_GameplayEffect.h"

#include "Relic.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API URelic : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UStaticMesh* MyMesh;

	UPROPERTY(EditDefaultsOnly)
		FLH_GameplayEffect Effect;

	UPROPERTY(EditAnywhere)
		bool bIsInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText Modifiers;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText Values;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UTexture2D* Icon;
};
