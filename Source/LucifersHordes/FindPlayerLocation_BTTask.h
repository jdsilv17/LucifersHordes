// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FindPlayerLocation_BTTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LUCIFERSHORDES_API UFindPlayerLocation_BTTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindPlayerLocation_BTTask(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess = "true"))
		bool bSearchRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess = "true"))
		float SearchArea = 150.0f;
};
