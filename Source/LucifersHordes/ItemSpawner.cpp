// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < WeaponLootTable.Num()-1; i++) {
		if (WeaponLootTable[i].weight == 0)
			WeaponLootTable[i].weight = 1;
		for (int currW = 0; currW < WeaponLootTable[i].weight; currW++) {
			WeightedWeapon.Add(WeaponLootTable[i]);
		}
	}
	for (int i = 0; i < RelicLootTable.Num()-1; i++) {
		if (RelicLootTable[i].weight == 0)
			RelicLootTable[i].weight = 1;
		for (int currW = 0; currW < RelicLootTable[i].weight; currW++) {
			WeightedRelic.Add(RelicLootTable[i]);
		}
	}
	for (int i = 0; i < PlayerAbilityTable.Num()-1; i++) {
		if (PlayerAbilityTable[i].weight == 0)
			PlayerAbilityTable[i].weight = 1;
		for (int currW = 0; currW < PlayerAbilityTable[i].weight; currW++) {
			WeightedPAbility.Add(PlayerAbilityTable[i]);
		}
	}
	for (int i = 0; i < WeaponAbilityTable.Num()-1; i++) {
		if (WeaponAbilityTable[i].weight == 0)
			WeaponAbilityTable[i].weight = 1;
		for (int currW = 0; currW < WeaponAbilityTable[i].weight; currW++) {
			WeightedWAbility.Add(WeaponAbilityTable[i]);
		}
	}

	for (int i = 0; i < WeaponWeight; i++) {
		ItemTypeWeight.Add(EItemType::Weapon);
	}
	for (int i = 0; i < RelicWeight; i++) {
		ItemTypeWeight.Add(EItemType::Relic);
	}
	for (int i = 0; i < AbilityWeight; i++) {
		ItemTypeWeight.Add(EItemType::Ability);
	}
}

void AItemSpawner::SpawnItem(FVector loc)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AGroundItem* item = World->SpawnActor<AGroundItem>(groundItemRefrence, loc, FRotator(0.0f), spawnParams);

	PickItem(item);
}

void AItemSpawner::SpawnItem(FVector loc, EItemType type)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AGroundItem* item = World->SpawnActor<AGroundItem>(groundItemRefrence, loc, FRotator(0.0f), spawnParams);

	if (type == EItemType::Weapon) {
		PickWeapon(item);
	}
	else if (type == EItemType::Ability) {
		PickAbility(item);
	}
	else {
		PickRelic(item);
	}
}

void AItemSpawner::PickItem(AGroundItem* item)
{
	switch (ItemTypeWeight[FMath::RandRange(0, ItemTypeWeight.Num() - 1)]) {
	case EItemType::Weapon:
		PickWeapon(item);
		break;
	case EItemType::Ability:
		PickAbility(item);
		break;
	case EItemType::Relic:
		PickRelic(item);
		break;
	}
	//if (FMath::FRand() < WeaponProb) {
	//	//Get Weapon
	//	PickWeapon(item);
	//	
	//}
	//else {
	//	//Get Relic
	//	PickRelic(item);
	//}
}

void AItemSpawner::PickWeapon(AGroundItem* item) {
	item->SetMyWeapon(WeightedWeapon[FMath::RandRange(0, WeightedWeapon.Num() - 1)].Weapon);
	item->itemType = EItemType::Weapon;
	if(FMath::FRand() < WeaponAbilityProb)
		item->SetWepAbility(WeightedWAbility[FMath::RandRange(0, WeightedWAbility.Num() - 1)].Ability);
}

void AItemSpawner::PickRelic(AGroundItem* item) {
	item->SetMyRelic(WeightedRelic[FMath::RandRange(0, WeightedRelic.Num() - 1)].Relic);
	item->itemType = EItemType::Relic;
}

void AItemSpawner::PickAbility(AGroundItem* item) {
	item->SetMyAbility(WeightedPAbility[FMath::RandRange(0, WeightedPAbility.Num() - 1)].Ability);
	item->itemType = EItemType::Ability;
}

