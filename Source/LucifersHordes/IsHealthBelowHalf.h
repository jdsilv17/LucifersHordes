// Fill out your copyright notice in the Description page of Project Settings.
//This is the service that will check to see if the boss health falls below half
// so it can enter his enraged state. 
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BaseCharacter.h"
#include "IsHealthBelowHalf.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UIsHealthBelowHalf : public UBTService
{
	GENERATED_BODY()
	
public: 
	UIsHealthBelowHalf(); 
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_mem) override; 

};
