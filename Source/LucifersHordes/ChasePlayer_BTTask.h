// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "RootEnemyCharacter.h"
#include "ChasePlayer_BTTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UChasePlayer_BTTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UChasePlayer_BTTask(FObjectInitializer const& objectInit);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_mem) override;
};
