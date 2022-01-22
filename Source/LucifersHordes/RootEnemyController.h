// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "RootEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API ARootEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	ARootEnemyController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* const pawn) override;
	
	class UBlackboardComponent* get_Blackboard() const;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BTreeComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BTree;

	class UBlackboardComponent* BBComp = nullptr;

	class UAISenseConfig_Sight* MySight;

	UFUNCTION()
		void on_target_detected(AActor* actor, FAIStimulus const stimulus);

	virtual void setup_perception_system();
};
