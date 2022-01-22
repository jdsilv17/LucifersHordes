// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BossEnemyCharacter.h"
#include "LongRangeAttack.generated.h"

/**
 * 
 * For to name it right but this is the Task Node for the Long range attack that the boss could do depending on the players distance from him 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API ULongRangeAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public: 
	ULongRangeAttack(FObjectInitializer const& obj_init); 

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override; 

private: 
	bool MontageEnded(ABossEnemyCharacter* const boss); 
};
