// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUCIFERSHORDES_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
		int32 MeleeAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
		int32 WhenDamaged(AActor* DamageCauser);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
		int32 LongRangeAttack(); 

	// i think this is stupid
	// not sure about making these events
	UFUNCTION(BlueprintNativeEvent)
		bool AttackBegin();
	UFUNCTION(BlueprintNativeEvent)
		bool IsAttacking(FVector HitLocation);
	UFUNCTION(BlueprintNativeEvent)
		bool AttackEnd();
	UFUNCTION(BlueprintNativeEvent)
		float GetCapsuleColliderRadius() const;
};
