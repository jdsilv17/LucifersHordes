// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

#include "BaseCharacter.h"

#include "LH_GameplayStatics.generated.h"

//class ABaseCharacter;
enum class EDamageTypes : uint8;

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API ULH_GameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		static float ApplyDamage_(ABaseCharacter* DamagedCharacter, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass, TArray<EDamageTypes> DamageTypes);
};
