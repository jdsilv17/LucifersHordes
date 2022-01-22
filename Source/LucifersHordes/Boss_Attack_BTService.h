// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Boss_Attack_BTService.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UBoss_Attack_BTService : public UBTService
{
	GENERATED_BODY()

public: 
	UBoss_Attack_BTService(); 
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override; 
private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float MeleeAttack_Range = 25.0f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float LongAttack_Range = 300.0f;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	//	bool bAttacking; 
};
