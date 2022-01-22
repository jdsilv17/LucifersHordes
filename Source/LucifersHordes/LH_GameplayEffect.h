// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LH_GameplayEffect.generated.h"

UENUM()
enum class EDamageTypes : uint8
{
	None			UMETA(DisplayName = "None"),
	Fire			UMETA(DisplayName = "Fire"),
	Ice				UMETA(DisplayName = "Ice"),
	Heal			UMETA(DisplayName = "Heal"),
	LifeStealTo		UMETA(DisplayName = "Lifesteal To"),
	LifeStealFrom	UMETA(DisplayName = "Lifesteal From")
};

UENUM()
enum class EAttributes : uint8
{
	None		UMETA(DisplayName = "None"),
	Health		UMETA(DisplayName = "Health"),
	Defense		UMETA(Displayname = "Defense"),
	MaxHealth	UMETA(DisplayName = "Max Health"),
	FireRes		UMETA(DisplayName = "Fire Resistance"),
	IceRes		UMETA(DisplayName = "Ice Resistance"),
	Lifesteal	UMETA(DisplayName = "Lifesteal")
};

USTRUCT(BlueprintType)
struct FModifier
{
	GENERATED_BODY()

public:
	FModifier()
		: AttributeToEffect(EAttributes::None), AttributeModifier(0.0f) {}
	FModifier(EAttributes _attribute, float _modifierVal)
		: AttributeToEffect(_attribute), AttributeModifier(_modifierVal) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EAttributes AttributeToEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float AttributeModifier;
};

USTRUCT(BlueprintType)
struct LUCIFERSHORDES_API FLH_GameplayEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FModifier> Modifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EDamageTypes DamageType = EDamageTypes::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bIsTemporary = false;
};
