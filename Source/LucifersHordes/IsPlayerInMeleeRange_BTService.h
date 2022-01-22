// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsPlayerInMeleeRange_BTService.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UIsPlayerInMeleeRange_BTService : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UIsPlayerInMeleeRange_BTService();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_Mem) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float meleeRange = 25.0f;
};
