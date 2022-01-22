// Fill out your copyright notice in the Description page of Project Settings.


#include "BTAttacking.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LucifersHordesCharacter.h"
#include "BaseEnemyAI.h"

EBTNodeResult::Type UBTAttacking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyAIController* BaseCon = Cast<AEnemyAIController>(OwnerComp.GetOwner());
    ABaseEnemyAI* BaseEnemy = Cast<ABaseEnemyAI>(OwnerComp.GetOwner()); 
    ALucifersHordesCharacter* Chacater = Cast<ALucifersHordesCharacter>(OwnerComp.GetOwner()); 
    float meleeRange = 500.0f; 

    //if (BaseCon)
    //{
    //    /*Getting the BB comp*/
    //    UBlackboardKeyType* BBComp = nullptr; 

    //    if (BaseEnemy->GetDistanceTo(BaseEnemy->GetOwner()) && Chacater->GetDistanceTo() <= meleeRange)
    //    {
    //        /*BBComp->SetValueAsBool("PlayerIsInMeleeRange"); */
    //    }
    //}

    // because you forgot to set a return value so I couldn't rebuild the project
    return EBTNodeResult::Failed;
}
