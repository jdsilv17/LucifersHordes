// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BossEnemyCharacter.h"
#include "Long_AttackBTTask_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API ULong_AttackBTTask_BlackboardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	ULong_AttackBTTask_BlackboardBase(FObjectInitializer const& obj_init); 
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override; 

private: 
	bool MontageEnded(ABossEnemyCharacter* const boss); 
};
