// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GroundItem.h"
#include "ItemTypes.h"
#include "Ability.h"

#include "ItemSpawner.generated.h"



USTRUCT()
struct FWeaponLootDrop {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AMeleeWeapon> Weapon;
	UPROPERTY(EditAnywhere)
		int weight = 1;
};

USTRUCT()
struct FRelicLootDrop {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<URelic> Relic;
	UPROPERTY(EditAnywhere)
		int weight = 1;
};

USTRUCT()
struct FAbilityLoot {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UAbility> Ability;
	UPROPERTY(EditAnywhere)
		int weight = 1;
};

//USTRUCT()
//struct FLootDrop {
//
//	GENERATED_BODY()
//
//public:
//	/*
//	*	Change this as well, this should just be like a refernece to a data Asset or ground item
//	*/
//	UPROPERTY(EditAnywhere)
//		bool bIsWeapon;
//
//	UPROPERTY(EditAnywhere, Meta = (EditCondition = "!bIsWeapon"))
//		TSubclassOf<URelic> relic;
//
//	UPROPERTY(EditAnywhere, Meta = (EditCondition = "bIsWeapon"))
//		TSubclassOf<AMeleeWeapon> weapon;
//
//	//UPROPERTY(EditAnywhere)
//	//	EItemType itemType;
//	/********************************************************/
//
//	UPROPERTY(EditAnywhere)
//		int32 ID;
//
//	UPROPERTY(EditAnywhere)
//		float weight;
//};

UCLASS()
class LUCIFERSHORDES_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AItemSpawner();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//UPROPERTY(EditAnywhere)
	//	TArray<FLootDrop> LootTable;
	UPROPERTY(EditAnywhere, Category = "Loot Tables")
		TArray<FWeaponLootDrop> WeaponLootTable;

	UPROPERTY(EditAnywhere, Category = "Loot Tables")
		TArray<FRelicLootDrop> RelicLootTable;

	UPROPERTY(EditAnywhere, Category = "Loot Tables")
		TArray<FAbilityLoot> PlayerAbilityTable;

	UPROPERTY(EditAnywhere, Category = "Loot Tables")
		TArray<FAbilityLoot> WeaponAbilityTable;


	TArray<FWeaponLootDrop> WeightedWeapon;
	TArray<FRelicLootDrop> WeightedRelic;
	TArray<FAbilityLoot> WeightedPAbility;
	TArray<FAbilityLoot> WeightedWAbility;

	UPROPERTY(EditAnywhere, Category = "Weapon Ability Probablitiy")
		float WeaponAbilityProb = 0.5f;

	TArray<EItemType> ItemTypeWeight;

	UPROPERTY(EditAnywhere, Category = "Loot Weights")
		int WeaponWeight;
	UPROPERTY(EditAnywhere, Category = "Loot Weights")
		int RelicWeight;
	UPROPERTY(EditAnywhere, Category = "Loot Weights")
		int AbilityWeight;

	/*
	*	Please keep naming conventions consistant, I know some of this was probably Kurtis but still
	*/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> groundItemRefrence;

public:	

	/*
	*	Should probably be using an interface to call this function in enemy and anywhere else
	*/
	void SpawnItem(FVector loc);
	void SpawnItem(FVector loc, EItemType type);

	// Keep Function naming conventions
	void PickItem(AGroundItem* item);
	void PickWeapon(AGroundItem* item);
	void PickRelic(AGroundItem* item);
	void PickAbility(AGroundItem* item);

};
