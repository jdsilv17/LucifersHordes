// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BossEnemyCharacter.h"
#include "Boss_Perform_Attack_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UBoss_Perform_Attack_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBoss_Perform_Attack_BTTaskNode(FObjectInitializer const& object_init); 

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override; 

private: 
	bool montageEnded(ABossEnemyCharacter* const enemy); 

};
