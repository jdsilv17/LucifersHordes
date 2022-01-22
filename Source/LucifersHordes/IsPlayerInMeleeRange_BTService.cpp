// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInMeleeRange_BTService.h"

#include "RootEnemyController.h"
#include "RootEnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboardKeys.h"

UIsPlayerInMeleeRange_BTService::UIsPlayerInMeleeRange_BTService()
{
	this->bNotifyBecomeRelevant = true;
	this->NodeName = TEXT("Is Player In Melee Range");
}
void UIsPlayerInMeleeRange_BTService::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_Mem)
{
	Super::OnBecomeRelevant(owner_comp, node_Mem);

	//get enemy controller
	ARootEnemyController* const cont = Cast<ARootEnemyController>(owner_comp.GetAIOwner());
	//get enemy
	ARootEnemyCharacter* const enemy = Cast<ARootEnemyCharacter>(cont->GetPawn());

	//find player and get distance
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Cyan, FString::SanitizeFloat(enemy->GetDistanceTo(player)));
	cont->get_Blackboard()->SetValueAsBool(BB_Keys::playerIsInMeleeRange, enemy->GetDistanceTo(player) <= meleeRange);

}
