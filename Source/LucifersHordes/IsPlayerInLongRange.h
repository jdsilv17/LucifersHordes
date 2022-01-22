// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "IsPlayerInLongRange.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UIsPlayerInLongRange : public UBTService
{
	GENERATED_BODY()
	
public: 
	UIsPlayerInLongRange(); 
	
	void OnBecomeRelevant(UBehaviorTreeComponent& owner, uint8* N_memory) override; 

private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float long_range_attack = 300.0f; 
};
