// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ItemSpawner.h"
#include "LH_GameplayEffect.h"
#include "UIManagerGameInstance.h"

#include "Attributes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUCIFERSHORDES_API UAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributes();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defense & Resistances")
		float Defense = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defense & Resistances")
		float FireResistance = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defense & Resistances")
		float IceResistance = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lifesteal")
		float Lifesteal = 0.0f;

	void ApplyEffect(FLH_GameplayEffect Effect);

	UFUNCTION(BlueprintCallable)
		const float GetMaxHealth() const { return this->MaxHealth; }
	UFUNCTION(BlueprintCallable)
		const float GetCurrentHealth() const { return this->CurrentHealth; }
	UFUNCTION(BlueprintCallable)
		void SetMaxHealth(const float health) { MaxHealth = health; }
	UFUNCTION(BlueprintCallable)
		void SetCurrentHealth(const float health) { CurrentHealth = health; }

protected:
	virtual void BeginPlay() override;

	//virtual void EndPlay(EEndPlayReason::Type end) override;

private:
	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		float CurrentHealth;

	UFUNCTION()
		void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION()
		void OnTakeDefaultDamage(AActor* DamagedActor, float Damage, TArray<EDamageTypes> DamageTypes, class AController* InstigatedBy, AActor* DamageCauser);


};
