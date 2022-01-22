// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Ability.h"

#include "AbilityComponent.generated.h"

class UAbility;
struct FAbilityData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUCIFERSHORDES_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

	bool bActivated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateAbility(FName Key);

	void AddAbility(UAbility* ability);
	void AddPAbility(UAbility* ability);
	void RemoveAbility(FName Key);

private:
	UAbility* ActiveAbility;

	TMap<FName, UAbility*> SlottedAbilities;

	bool bEffectApplied;
		
};
