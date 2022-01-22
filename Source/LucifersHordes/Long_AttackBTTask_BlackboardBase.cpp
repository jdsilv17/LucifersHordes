// Fill out your copyright notice in the Description page of Project Settings.


#include "Long_AttackBTTask_BlackboardBase.h"
#include "CombatInterface.h"
#include "BossEnemyController.h"
#include "BossEnemyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "blackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

ULong_AttackBTTask_BlackboardBase::ULong_AttackBTTask_BlackboardBase(FObjectInitializer const& obj_init)
{
	this->NodeName = TEXT("Long Range Attack Task");
}

EBTNodeResult::Type ULong_AttackBTTask_BlackboardBase::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ABossEnemyController* const cont = Cast<ABossEnemyController>(owner_comp.GetAIOwner()); 
	ABossEnemyCharacter* const boss = Cast<ABossEnemyCharacter>(cont->GetPawn()); 

  
	if (ICombatInterface* const com = Cast<ICombatInterface>(boss))
	{
		if (this->MontageEnded(boss))
		{
			com->Execute_LongRangeAttack(boss); 
		}
	}
	this->FinishLatentTask(owner_comp, EBTNodeResult::Succeeded); 
	return EBTNodeResult::Succeeded; 
}

bool ULong_AttackBTTask_BlackboardBase::MontageEnded(ABossEnemyCharacter* const boss)
{
	if (true)
	{
		return boss->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(boss->getMontage()); 
	}
	return false; 
}