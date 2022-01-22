// Fill out your copyright notice in the Description page of Project Settings.


#include "AmDead_BTService.h"

#include "RootEnemyController.h"
#include "RootEnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboardKeys.h"

UAmDead_BTService::UAmDead_BTService()
{
	this->bNotifyBecomeRelevant = true;
	this->NodeName = TEXT("Am I Dead");
}
void UAmDead_BTService::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_Mem)
{
	Super::OnBecomeRelevant(owner_comp, node_Mem);

	//Get controller then enemy
	ARootEnemyController* cont = Cast<ARootEnemyController>(owner_comp.GetAIOwner());
	ARootEnemyCharacter* enemy = Cast<ARootEnemyCharacter>(cont->GetPawn());

	cont->get_Blackboard()->SetValueAsBool(BB_Keys::IAmDead, enemy->bDead);


}