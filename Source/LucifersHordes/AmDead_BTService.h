// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "AmDead_BTService.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UAmDead_BTService : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UAmDead_BTService();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_Mem) override;
};
