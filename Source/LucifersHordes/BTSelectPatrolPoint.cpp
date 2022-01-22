// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectPatrolPoint.h"
#include "AIPatrolPoint.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

    if (AICon)
    {
        /*get BB component*/
        UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

        AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

        TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

        AAIPatrolPoint* NextPatrolPoint = nullptr;

        //checks to see if there are no points in the world. 
        if (AvailablePatrolPoints.Num() == 0) {
            return EBTNodeResult::Succeeded;
        }

        /*checks to see if there is any points to walk to and if not it will go back to the start*/
        if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
        {
            NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]);
        }
        else /*if there is not any more points to go to, just go back to the start. */
        {
            NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);
            AICon->CurrentPatrolPoint = 0;
        }

        BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;

}
