// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RootEnemyCharacter.h"
#include "BossEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API ABossEnemyCharacter : public ARootEnemyCharacter
{
	GENERATED_BODY()
	
public: 
	int MeleeAttack_Implementation() override; 
	int LongRangeAttack_Implementation() override; 


protected: 
	void BeginPlay() override; 

private: 
	UPROPERTY(EditDefaultsOnly, Category = "Animation") 
		UAnimMontage* AttackMontage; 

	UPROPERTY(EditDefaultsOnly, Category = "Animation") 
		UAnimMontage* PowerUpMon; 

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathMon; 

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* LongRangeAttack;
};
