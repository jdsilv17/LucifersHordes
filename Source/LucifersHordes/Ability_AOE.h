// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Ability_AOE.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API UAbility_AOE : public UAbility
{
	GENERATED_BODY()
	
public:
	virtual void ExecuteAbility() override;

	virtual void Tick(float DeltaTime) override;

	virtual void CoolDown(float DeltaTime) override;

	virtual void Reset() override;

private:
	UPROPERTY(EditDefaultsOnly)
		float DamageToApply = 0.0f;
	UPROPERTY(EditDefaultsOnly)
		float Radius = 200.0f;
	UPROPERTY(EditDefaultsOnly)
		float LaunchInfluence = 500.0f;
};
