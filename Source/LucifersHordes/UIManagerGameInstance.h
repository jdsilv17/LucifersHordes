// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UIManagerGameInstance.generated.h"

class UAttributes;
class AMeleeWeapon;
class UAbility;
class ALucifersHordesCharacter;

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API UUIManagerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UUIManagerGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int totalKillCount = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int globalKillCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int swordKillCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int daggerKillCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int hammerKillCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int morningKillCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int breadKillCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int tempSwordKills = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int tempDaggerKills = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int tempHammerKills = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int tempMorningKills = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	int tempBreadKills = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int fireResistItemCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int iceResistItemCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int poisonResistItemCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int stunResistItemCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int defenseItemCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int enduranceItemCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int lifestealItemCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int completedRuns = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int currLevelsCleared = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int globalLevelsCleared = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Challenges")
	bool isDejavuComplete = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Challenges")
	int silverCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	int playerDeathCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	int highestLevelCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	int highestKillCount = 0;

	/***************************** Attributes ******************************************/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Defense & Resistances")
		float Defense = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Defense & Resistances")
		float FireResistance = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Defense & Resistances")
		float IceResistance = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lifesteal")
		float Lifesteal = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AMeleeWeapon* weapon;

	TSubclassOf<AMeleeWeapon> PlayerWeapon;
	TSubclassOf<UAbility> PlayerAbility;
	TSubclassOf<UAbility> WeaponAbility;

	bool SavePlayerData(ALucifersHordesCharacter* player);

	bool LoadPlayerData(ALucifersHordesCharacter* player);

	UFUNCTION(BlueprintCallable)
		void Reset();

private:
		bool bIsPlayerDataSaved;
		bool bPlayerDataReset;
};
