// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer_BTTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "RootEnemyController.h"
#include "blackboardKeys.h"
#include "GameFramework/CharacterMovementComponent.h"



UChasePlayer_BTTask::UChasePlayer_BTTask(FObjectInitializer const& objectInit)
{
	this->NodeName = TEXT("ChasePlayer");
}

EBTNodeResult::Type UChasePlayer_BTTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_mem)
{
	//Get updated location of player
	ARootEnemyController* cont = Cast<ARootEnemyController>(owner_comp.GetAIOwner());
	const ARootEnemyCharacter* enemy = Cast<ARootEnemyCharacter>(cont->GetPawn());

	// if the enemy is not damaged then move
	if (!enemy->bIsDamaged || !enemy->GetMovementComponent()->IsFalling())
	{
		FVector const playerLoc = cont->get_Blackboard()->GetValueAsVector(BB_Keys::Target_Location);

		//Move to enemy loc
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, playerLoc);

		//Finish
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
