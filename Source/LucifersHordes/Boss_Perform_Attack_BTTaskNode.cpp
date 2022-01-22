// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Perform_Attack_BTTaskNode.h"
#include "CombatInterface.h"
#include "BossEnemyController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "blackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBoss_Perform_Attack_BTTaskNode::UBoss_Perform_Attack_BTTaskNode(FObjectInitializer const& object_init)
{
	this->NodeName = TEXT("Boss Perform Attack"); 
}

EBTNodeResult::Type UBoss_Perform_Attack_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//getting the bosses controller
	ABossEnemyController* const controller = Cast<ABossEnemyController>(owner_comp.GetAIOwner()); 
	
	//Get the enemy character 
	ABossEnemyCharacter* const boss = Cast<ABossEnemyCharacter>(controller->GetPawn()); 

	if (!controller->get_Blackboard()->GetValueAsBool(BB_Keys::playerIsInMeleeRange) && !controller->get_Blackboard()->GetValueAsBool(BB_Keys::PlayerIsInLongRange))
		return EBTNodeResult::Failed; 

	if (ICombatInterface* const combat = Cast<ICombatInterface>(boss))
	{
		if (this->montageEnded(boss))
		{
			combat->Execute_MeleeAttack(boss);
			combat->Execute_LongRangeAttack(boss); 
		}
	}
	this->FinishLatentTask(owner_comp, EBTNodeResult::Succeeded); 
	return EBTNodeResult::Succeeded; 
}

bool UBoss_Perform_Attack_BTTaskNode::montageEnded(ABossEnemyCharacter* const enemy)
{
	if (true)
	{
		return enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(enemy->getMontage()); 
	}

	return false; 
}