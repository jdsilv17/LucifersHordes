// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ItemTypes.generated.h"

/**
 * 
 */
 UENUM(Blueprinttype)
 enum class EItemType : uint8
 {
 	None		UMETA(DisplayName = "None"),
 	Weapon		UMETA(DisplayName = "Weapon"),
 	Relic		UMETA(DisplayName = "Relic"),
    Ability		UMETA(DisplayName = "Ability")
 };