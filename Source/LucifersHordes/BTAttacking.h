// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTAttacking.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API UBTAttacking : public UBTTaskNode
{
	GENERATED_BODY()
	
		/*it will excute the attacking task that I make*/
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
};
