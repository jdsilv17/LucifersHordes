// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSelectPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API UBTSelectPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
		/*will execute a task that we define ourselves*/
		/*and we are making our own behavior tree task*/
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
};
