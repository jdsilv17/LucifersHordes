// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LH_DataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class LUCIFERSHORDES_API ULH_DataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	ULH_DataAsset() : ID(0), Name(TEXT("Asset")) {}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		FPrimaryAssetType AssetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		int32 Count;
};
