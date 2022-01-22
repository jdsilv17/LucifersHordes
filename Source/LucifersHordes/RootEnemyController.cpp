// Fill out your copyright notice in the Description page of Project Settings.


#include "RootEnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LucifersHordesCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "blackboardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
 
ARootEnemyController::ARootEnemyController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/Enemies/EnemyFolder/RootEnemy_BT.RootEnemy_BT'"));
	if (obj.Succeeded()) {
		this->BTree = obj.Object;
	}
	this->BTreeComp = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviourComp"));

	this->BBComp = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	this->setup_perception_system();
}

void ARootEnemyController::BeginPlay()
{
	Super::BeginPlay();

	this->RunBehaviorTree(this->BTree);

	this->BTreeComp->StartTree(*this->BTree);
}

void ARootEnemyController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	
	if (this->BBComp)
	{
		this->BBComp->InitializeBlackboard(*BTree->BlackboardAsset);
	}
}

UBlackboardComponent* ARootEnemyController::get_Blackboard() const
{
	return this->BBComp;
}

void ARootEnemyController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const ch = Cast<ALucifersHordesCharacter>(actor)) {
		this->get_Blackboard()->SetValueAsBool(BB_Keys::bCanSeePlayer, stimulus.WasSuccessfullySensed());
	}
}

void ARootEnemyController::setup_perception_system()
{
	this->MySight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	this->SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perceptioin Comp")));

	this->MySight->SightRadius = 1500.0f;
	this->MySight->LoseSightRadius = MySight->SightRadius + 50.0f;
	this->MySight->PeripheralVisionAngleDegrees = 180.0f;
	this->MySight->SetMaxAge(5.0f);
	this->MySight->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	this->MySight->DetectionByAffiliation.bDetectEnemies = true;
	this->MySight->DetectionByAffiliation.bDetectFriendlies = true;
	this->MySight->DetectionByAffiliation.bDetectNeutrals = true;

	//add sight config to percept comp
	this->GetPerceptionComponent()->SetDominantSense(*MySight->GetSenseImplementation());
	this->GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ARootEnemyController::on_target_detected);
	this->GetPerceptionComponent()->ConfigureSense(*MySight);
}
