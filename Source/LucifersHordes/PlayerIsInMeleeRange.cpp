// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerIsInMeleeRange.h"
#include "BaseEnemyAI.h"
#include "EnemyAIController.h"
#include "LucifersHordesCharacter.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

//void UPlayerIsInMeleeRange::OnBecomeRelevant(UBlackboardComponent& owner_comp, uint8* NodeMemory)
//{
//	Super::OnBecomeRelevant(owner_comp, NodeMemory);
//
//	/*Getting the AI*/
//	AEnemyAIController* EnemyCon = Cast<AEnemyAIController>(owner_comp.GetOwner());
//	ABaseEnemyAI* BaseEnemy = Cast<ABaseEnemyAI>(EnemyCon->GetPawn()); 
//
//	/*Getting the Player character*/
//	ALucifersHordesCharacter* Player = Cast<ALucifersHordesCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)); 
//
//	EnemyCon->GetBlackboardComp()->SetValueAsBool("PlayerIsInMeleeRange", BaseEnemy->GetDistanceTo(Player) <= melee_range); 
//
//}
