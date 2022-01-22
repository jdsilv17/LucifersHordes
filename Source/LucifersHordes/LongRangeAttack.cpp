// Fill out your copyright notice in the Description page of Project Settings.


#include "LongRangeAttack.h"
#include "CombatInterface.h"
#include "BossEnemyController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "blackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

ULongRangeAttack::ULongRangeAttack(FObjectInitializer const& obj_init)
{
	this->NodeName = TEXT("Long Range Attack"); 
}

EBTNodeResult::Type ULongRangeAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ABossEnemyController* const controller = Cast<ABossEnemyController>(owner_comp.GetAIOwner()); 
	ABossEnemyCharacter* const boss = Cast<ABossEnemyCharacter>(controller->GetPawn()); 

	if (ICombatInterface* const combat = Cast<ICombatInterface>(boss))
	{
		if (this->MontageEnded(boss))
		{
			combat->Execute_LongRangeAttack(boss); 
		}
	}

	this->FinishLatentTask(owner_comp, EBTNodeResult::Succeeded); 
	return EBTNodeResult::Succeeded; 
}

bool ULongRangeAttack::MontageEnded(ABossEnemyCharacter* const boss)
{
	if (true)
	{
		return boss->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(boss->getMontage());
	}

	return false; 
}