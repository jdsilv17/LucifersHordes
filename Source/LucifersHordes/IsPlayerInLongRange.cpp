// Fill out your copyright notice in the Description page of Project Settings.
//Forgot it in the name but this is the Service that will check to see if the 
//player is far enough to where the boss has to do his leap attack to get close. 

#include "IsPlayerInLongRange.h"

#include "BossEnemyCharacter.h"
#include"BossEnemyController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboardKeys.h"

UIsPlayerInLongRange::UIsPlayerInLongRange()
{
	this->bNotifyBecomeRelevant = true; 
	this->NodeName = TEXT("Is Player In Long Range"); 
}

void UIsPlayerInLongRange::OnBecomeRelevant(UBehaviorTreeComponent& owner, uint8* N_memory)
{
	Super::OnBecomeRelevant(owner, N_memory); 

	ABossEnemyController* const controller = Cast<ABossEnemyController>(owner.GetAIOwner()); 

	ABossEnemyCharacter* const boss = Cast<ABossEnemyCharacter>(controller->GetPawn()); 

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0); 

	controller->get_Blackboard()->SetValueAsBool(BB_Keys::PlayerIsInLongRange, boss->GetDistanceTo(player) <= long_range_attack); 
}