// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LH_AssetManager.generated.h"

class ULH_DataAsset;
/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API ULH_AssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	ULH_AssetManager() {}
	//virtual void StartInitialLoading() override;
	// types of Assets
	static const FPrimaryAssetType RelicItemType;
	static const FPrimaryAssetType WeaponItemType;

	static ULH_AssetManager& Get();

	ULH_DataAsset* ForceGetDA(const FPrimaryAssetId& primaryAssetId, bool bLogWarning = false);
};
