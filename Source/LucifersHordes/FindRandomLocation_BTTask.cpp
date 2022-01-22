// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation_BTTask.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "RootEnemyController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "blackboardKeys.h"
#include "EnemySpawnPoint.h"
#include "RootEnemyCharacter.h"

UFindRandomLocation_BTTask::UFindRandomLocation_BTTask(FObjectInitializer const& objectInitializer)
{
	this->NodeName = TEXT("FindRandomLocation");
}

EBTNodeResult::Type UFindRandomLocation_BTTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//get AI cont and enemy
	auto const cont = Cast<ARootEnemyController>(owner_comp.GetAIOwner());

	auto const enemy = cont->GetPawn();

	//auto const enemy_char = Cast<ARootEnemyCharacter>(enemy); 

	//Get the spanwer 
	//auto const* spawner = Cast<AEnemySpawnPoint>(owner_comp.GetOwner());

	
		//Get Pawn Location

		FVector const origin = enemy->GetTargetLocation();
		FNavLocation loc;

		////Get the Spawner location 
		FVector const spawn_origin;

		//get nav system. Get Random location
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(origin, SearchRadius, loc, nullptr)) {
			cont->get_Blackboard()->SetValueAsVector(BB_Keys::Target_Location, loc.Location);
		}
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	

	return EBTNodeResult::Succeeded;
}
