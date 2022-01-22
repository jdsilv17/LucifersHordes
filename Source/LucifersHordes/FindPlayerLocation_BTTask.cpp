// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation_BTTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RootEnemyController.h"
#include "GameFramework/Character.h"
#include "blackboardKeys.h"

UFindPlayerLocation_BTTask::UFindPlayerLocation_BTTask(FObjectInitializer const& object_initializer)
{
	this->NodeName = TEXT("Find Player Location");
}
EBTNodeResult::Type UFindPlayerLocation_BTTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//get Player and npc controller

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const cont = Cast<ARootEnemyController>(owner_comp.GetAIOwner());

	//Get player loc
	FVector const playerLocation = player->GetActorLocation();

	if (bSearchRandom)
	{
		FNavLocation loc;

		//Get nav system and get a place near the player
		UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());

		if (navSys->GetRandomPointInNavigableRadius(playerLocation, SearchArea, loc))
		{
			cont->get_Blackboard()->SetValueAsVector(BB_Keys::Target_Location, loc.Location);
		}
	}
	else
	{
		cont->get_Blackboard()->SetValueAsVector(BB_Keys::Target_Location, playerLocation);
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
