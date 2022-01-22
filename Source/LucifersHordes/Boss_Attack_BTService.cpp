// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Attack_BTService.h"
#include "BossEnemyCharacter.h"
#include "BossEnemyController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboardKeys.h"
#include "GameFramework/Character.h"

UBoss_Attack_BTService::UBoss_Attack_BTService()
{
	this->bNotifyBecomeRelevant = true;
	this->NodeName = TEXT("Boss Attack");


	/*bAttacking = false;*/
}

void UBoss_Attack_BTService::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	//get the bosses controller
	ABossEnemyController* const cont = Cast<ABossEnemyController>(owner_comp.GetAIOwner());

	//Get the Boss character 
	ABossEnemyCharacter* const boss = Cast<ABossEnemyCharacter>(cont->GetPawn());

	//now get the distance of the player. 
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);


	//now time to do the check so it knows which one attack it should to do based off the distance and blackboard. 
	if (!boss->bIsAttacking)
	{
			cont->get_Blackboard()->SetValueAsBool(BB_Keys::playerIsInMeleeRange, boss->GetDistanceTo(player) <= MeleeAttack_Range);
			cont->get_Blackboard()->SetValueAsBool(BB_Keys::PlayerIsInLongRange,  boss->GetDistanceTo(player) <= LongAttack_Range);	
	}
}