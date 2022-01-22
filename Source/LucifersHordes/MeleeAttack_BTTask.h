// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "RootEnemyCharacter.h"
#include "MeleeAttack_BTTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UMeleeAttack_BTTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMeleeAttack_BTTask(FObjectInitializer const& object_init);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

private:
	bool montageHasEnded(ARootEnemyCharacter* const enemy);
	
};
