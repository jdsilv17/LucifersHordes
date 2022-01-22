// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Ability_TEST.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API UAbility_TEST : public UAbility
{
	GENERATED_BODY()
	
public:
	//UPROPERTY(EditDefaultsOnly)
	//	uint8 Rarity = 0;

	virtual void ExecuteAbility() override;

	virtual void Tick(float DeltaTime) override;

	virtual void CoolDown(float DeltaTime) override;

	virtual void Reset() override;
};
