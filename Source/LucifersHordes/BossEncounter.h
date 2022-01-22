// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomEncounter.h"
#include "BossEncounter.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API ABossEncounter : public ARoomEncounter
{
	GENERATED_BODY()

protected:

	void FinishedEncounter();
	int Died_Implementation();

	UPROPERTY(EditAnywhere)
		FName NextLevel;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ADoor> Door;
};
