// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAIController.generated.h"

/**
 *
 */
UCLASS()
class LUCIFERSHORDES_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	/*behavior tree component*/
	UBehaviorTreeComponent* BehaviorComp;

	/*Our blackboard component*/
	UBlackboardComponent* BlackboardComp;

	/*blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = AI) 
	FName LocationToGoKey; 

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey; 

	TArray<AActor*>PatrolPoints; 

	virtual void OnPossess(APawn* Pawn) override;

	

public:
	UPROPERTY(VisibleAnywhere)
	int32 CurrentPatrolPoint;

	AEnemyAIController();

	void SetPlayerCaught(APawn* Pawn); 


	/*Inline getter functions*/

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
};
