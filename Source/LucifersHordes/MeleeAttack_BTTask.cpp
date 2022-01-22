// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttack_BTTask.h"
#include "CombatInterface.h"
#include "RootEnemyController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "blackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"


UMeleeAttack_BTTask::UMeleeAttack_BTTask(FObjectInitializer const& object_init)
{
	this->NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UMeleeAttack_BTTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ARootEnemyController* const cont = Cast<ARootEnemyController>(owner_comp.GetAIOwner());
	ARootEnemyCharacter* const enemy = Cast<ARootEnemyCharacter>(cont->GetPawn());
	if (!cont->get_Blackboard()->GetValueAsBool(BB_Keys::playerIsInMeleeRange)) {
		return EBTNodeResult::Failed;
	}
	if (ICombatInterface* const icombat = Cast<ICombatInterface>(enemy))
	{
		if (this->montageHasEnded(enemy))
		{
			icombat->Execute_MeleeAttack(enemy);
		}
	}

	this->FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UMeleeAttack_BTTask::montageHasEnded(ARootEnemyCharacter* const enemy)
{
	if (true)
	{
		return enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(enemy->getMontage());
	}
	return false; 
}
