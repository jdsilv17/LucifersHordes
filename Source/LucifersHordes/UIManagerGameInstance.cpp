// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerGameInstance.h"
#include "LucifersHordesCharacter.h"

UUIManagerGameInstance::UUIManagerGameInstance()
{
	totalKillCount = 0;
	globalKillCount = 0;
	swordKillCount = 0;
	daggerKillCount = 0;
	hammerKillCount = 0;
	morningKillCount = 0;
	breadKillCount = 0;
	tempSwordKills = 0;
	tempDaggerKills = 0;
	tempHammerKills = 0;
	tempMorningKills = 0;
	tempBreadKills = 0;
	fireResistItemCount = 0;
	iceResistItemCount = 0;
	poisonResistItemCount = 0;
	stunResistItemCount = 0;
	defenseItemCount = 0;
	enduranceItemCount = 0;
	lifestealItemCount = 0;
	completedRuns = 0;
	currLevelsCleared = 0;
	globalLevelsCleared = 0;

	isDejavuComplete = false;
	silverCount = 0;
	playerDeathCount = 0;
	highestLevelCount = 0;
	highestKillCount = 0;

	CurrentHealth = MaxHealth = 0.0f;
	FireResistance = 0.0f;
	IceResistance = 0.0f;
	Lifesteal = 0.0f;

	weapon = nullptr;
	PlayerWeapon = nullptr;
	PlayerAbility = nullptr;
	WeaponAbility = nullptr;

	bIsPlayerDataSaved = false;
	bPlayerDataReset = false;
}

bool UUIManagerGameInstance::SavePlayerData(ALucifersHordesCharacter* player)
{
	if (bPlayerDataReset) return bPlayerDataReset = false;

	this->CurrentHealth		= player->GetAttributesComponent()->GetCurrentHealth();
	this->MaxHealth			= player->GetAttributesComponent()->GetMaxHealth();
	this->FireResistance	= player->GetAttributesComponent()->FireResistance;
	this->IceResistance		= player->GetAttributesComponent()->IceResistance;
	this->Lifesteal			= player->GetAttributesComponent()->Lifesteal;

	this->PlayerWeapon		= player->GetEquipedWeapon()->GetClass();

	UAbility* ability = player->TryGetAbility();
	if (ability)
		this->PlayerAbility		= ability->GetClass();

	UAbility* weaponAbility = player->GetEquipedWeapon()->TryGetAbility();
	if (weaponAbility)
		this->WeaponAbility		= weaponAbility->GetClass();

	return bIsPlayerDataSaved = true;
}

bool UUIManagerGameInstance::LoadPlayerData(ALucifersHordesCharacter* player)
{
	if (!bIsPlayerDataSaved) return false;

	player->GetAttributesComponent()->SetCurrentHealth(this->CurrentHealth);
	player->GetAttributesComponent()->SetMaxHealth(this->MaxHealth);
	player->GetAttributesComponent()->FireResistance = this->FireResistance;
	player->GetAttributesComponent()->IceResistance = this->IceResistance;
	player->GetAttributesComponent()->Lifesteal = this->Lifesteal;

	AMeleeWeapon* loadedWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(this->PlayerWeapon);
	loadedWeapon->SetAbility(this->WeaponAbility);
	player->ChangeWeapon(loadedWeapon);
	player->SetAbility(this->PlayerAbility);

	this->weapon = player->GetEquipedWeapon();

	bIsPlayerDataSaved = false;

	return true;
}

void UUIManagerGameInstance::Reset()
{
	totalKillCount = 0;
	//globalKillCount = 0;
	//swordKillCount = 0;
	//daggerKillCount = 0;
	//hammerKillCount = 0;
	//morningKillCount = 0;
	//breadKillCount = 0;
	tempSwordKills = 0;
	tempDaggerKills = 0;
	tempHammerKills = 0;
	tempMorningKills = 0;
	tempBreadKills = 0;
	fireResistItemCount = 0;
	iceResistItemCount = 0;
	//poisonResistItemCount = 0;
	//stunResistItemCount = 0;
	//defenseItemCount = 0;
	enduranceItemCount = 0;
	lifestealItemCount = 0;
	//completedRuns = 0;
	currLevelsCleared = 0;
	//globalLevelsCleared = 0;

	//isDejavuComplete = false;
	silverCount = 0;
	//playerDeathCount = 0;
	//highestLevelCount = 0;
	//highestKillCount = 0;

	CurrentHealth = MaxHealth = 100.0f;
	FireResistance = -0.15f;
	IceResistance = -0.15f;
	Lifesteal = 0.0f;

	weapon = nullptr;
	PlayerWeapon = nullptr;
	PlayerAbility = nullptr;
	WeaponAbility = nullptr;

	bIsPlayerDataSaved = false;
	bPlayerDataReset = true;
}
