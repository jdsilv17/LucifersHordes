// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "LH_GameplayEffect.h"

#include "EffectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEffectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUCIFERSHORDES_API IEffectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void ApplyEffectToAttribute(FLH_GameplayEffect EffectToApply) = 0;

	UFUNCTION()
	virtual void AddTempDamageType(EDamageTypes DamageType) = 0;
};
