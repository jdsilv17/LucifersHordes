// Fill out your copyright notice in the Description page of Project Settings.


#include "LH_AssetManager.h"
#include "LH_DataAsset.h"
//#include "AbilitySystemGlobals.h"

const FPrimaryAssetType ULH_AssetManager::RelicItemType = TEXT("Relic");
const FPrimaryAssetType ULH_AssetManager::WeaponItemType = TEXT("Weapon");

ULH_AssetManager& ULH_AssetManager::Get()
{
	ULH_AssetManager* LHAM = Cast<ULH_AssetManager>(GEngine->AssetManager);
	if (LHAM)
		return *LHAM;
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, needs to be LH_AssetManager"));
		return *NewObject<ULH_AssetManager>();
	}
}

ULH_DataAsset* ULH_AssetManager::ForceGetDA(const FPrimaryAssetId& primaryAssetId, bool bLogWarning)
{
	FSoftObjectPath assetPath = GetPrimaryAssetPath(primaryAssetId);

	ULH_DataAsset* gotItem = Cast<ULH_DataAsset>(assetPath.TryLoad());
	if (bLogWarning && gotItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get asset %s "), *primaryAssetId.ToString())
	}
	return gotItem;
}