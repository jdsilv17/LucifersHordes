// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "blackboardKeys.h"

ABossEnemyController::ABossEnemyController(FObjectInitializer const& obj_init)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>object(TEXT("BehaviorTree'/Game/Enemies/EnemyFolder/BossEnemy_BT.BossEnemy_BT'"));
	if (object.Succeeded())
		this->BTree = object.Object; 
}

void ABossEnemyController::setup_perception_system()
{
	this->MySight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("sight_config")); 

	this->SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("percep_config"))); 

	this->MySight->SightRadius = 3500.0f; 
	this->MySight->LoseSightRadius = MySight->SightRadius + 100.0f; 
	this->MySight->PeripheralVisionAngleDegrees = 180.0f; 
	this->MySight->SetMaxAge(5.0f); 
	this->MySight->AutoSuccessRangeFromLastSeenLocation = 1000.0f; 
	this->MySight->DetectionByAffiliation.bDetectEnemies = true; 
	this->MySight->DetectionByAffiliation.bDetectFriendlies = true; 
	this->MySight->DetectionByAffiliation.bDetectNeutrals = true; 

	this->GetPerceptionComponent()->SetDominantSense(*MySight->GetSenseImplementation()); 
	this->GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABossEnemyController::on_target_detected); 
	this->GetPerceptionComponent()->ConfigureSense(*MySight); 
}
