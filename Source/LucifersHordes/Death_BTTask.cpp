// Fill out your copyright notice in the Description page of Project Settings.


#include "Death_BTTask.h"
#include "DeathInterface.h"
#include "RootEnemyController.h"
#include "RootEnemyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboardKeys.h"

UDeath_BTTask::UDeath_BTTask(FObjectInitializer const& objectInit)
{
	NodeName = TEXT("Death");
}

EBTNodeResult::Type UDeath_BTTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_mem)
{
	ARootEnemyController* const cont = Cast<ARootEnemyController>(owner_comp.GetAIOwner());
	ARootEnemyCharacter* const enemy = Cast<ARootEnemyCharacter>(cont->GetPawn());

	if (IDeathInterface* const icombat = Cast<IDeathInterface>(enemy))
	{
		if (this->montageHasEnded(enemy))
		{
			icombat->Execute_Die(enemy);
		}
	}

	this->FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UDeath_BTTask::montageHasEnded(ARootEnemyCharacter* const enemy)
{
	return enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(enemy->getDeathMontage());
}
