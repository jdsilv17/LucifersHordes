// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RootEnemyController.h"
#include "BossEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API ABossEnemyController : public ARootEnemyController
{
	GENERATED_BODY()

public:
	ABossEnemyController(FObjectInitializer const& obj_init = FObjectInitializer::Get());

protected: 
	void setup_perception_system() override; 
	
};
