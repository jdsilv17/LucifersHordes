// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "LongAttackService_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API ULongAttackService_BlackboardBase : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	ULongAttackService_BlackboardBase(); 
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override; 

private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float range = 300.0f; 
};
