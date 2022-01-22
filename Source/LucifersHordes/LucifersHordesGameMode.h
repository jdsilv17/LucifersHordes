// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LucifersHordesGameMode.generated.h"

UCLASS(minimalapi)
class ALucifersHordesGameMode : public AGameModeBase
{
	GENERATED_BODY()



public:
	ALucifersHordesGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APawn* pPlayerPawnBPClass;
};



