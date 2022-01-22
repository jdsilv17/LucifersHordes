// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BaseEnemyAI.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

AEnemyAIController::AEnemyAIController()
{
	/*Initialize blackboard and behavior tree*/
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	/*initialize blackboard keys*/
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo"; 

	CurrentPatrolPoint = 0; 
}

void AEnemyAIController::SetPlayerCaught(APawn* pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, pawn); 
	}
}


void AEnemyAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn); 

	/*Get reference to the character*/
	ABaseEnemyAI* AICharacter = Cast<ABaseEnemyAI>(pawn);
	

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset)); 
		}

		/*Populate patrol point array*/
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*AICharacter->BehaviorTree); 
	}
}

