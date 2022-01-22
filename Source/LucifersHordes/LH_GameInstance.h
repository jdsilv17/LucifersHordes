// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"


#include "LH_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API ULH_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	ULH_GameInstance* GameInstance;
//private:

	UPROPERTY(EditAnywhere)
		float Health = 10000.0f;
	UPROPERTY(EditAnywhere)
		float MoveSpeedModifier = 1.0f;
};
