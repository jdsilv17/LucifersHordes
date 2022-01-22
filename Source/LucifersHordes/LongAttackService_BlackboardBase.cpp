// Fill out your copyright notice in the Description page of Project Settings.


#include "LongAttackService_BlackboardBase.h"
#include "BossEnemyCharacter.h"
#include "BossEnemyController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboardKeys.h"

ULongAttackService_BlackboardBase::ULongAttackService_BlackboardBase()
{
	this->bNotifyBecomeRelevant = true; 
	this->NodeName = TEXT("Is Player In Long Range Service");
}

void ULongAttackService_BlackboardBase::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory); 

	ABossEnemyController* const cont = Cast<ABossEnemyController>(owner_comp.GetAIOwner()); 
	
	ABossEnemyCharacter* const boss = Cast<ABossEnemyCharacter>(cont->GetPawn()); 

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0); 

	cont->get_Blackboard()->SetValueAsBool(BB_Keys::PlayerIsInLongRange, boss->GetDistanceTo(player) >= range); 
}
