// Fill out your copyright notice in the Description page of Project Settings.


#include "IsHealthBelowHalf.h"
#include "BossEnemyCharacter.h"
#include "BossEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboardKeys.h"

UIsHealthBelowHalf::UIsHealthBelowHalf()
{
	this->bNotifyBecomeRelevant = true; 
	this->NodeName = TEXT("Is Health Below Half"); 
}

void UIsHealthBelowHalf::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory); 

	//Get the enemy controller 
	ABossEnemyController* const cont = Cast<ABossEnemyController>(owner_comp.GetAIOwner()); 

	//Get the enemy character
	ABossEnemyCharacter* const Boss = Cast<ABossEnemyCharacter>(cont->GetPawn()); 

	//this is where it should check the health 
	if (Boss->GetAttributesComponent()->GetMaxHealth() / 2)
	{
		cont->get_Blackboard()->SetValueAsBool(BB_Keys::IsHealthBelowHalf, true);
	}
	else
		 Boss->GetAttributesComponent()->GetMaxHealth(); 
}