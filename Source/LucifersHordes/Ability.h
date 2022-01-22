// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "LH_GameplayEffect.h"

#include "Ability.generated.h"

UENUM()
enum class ECoolDownTier : uint8
{
	Custom			UMETA(DisplayName = "Custom"),
	Fast			UMETA(DisplayName = "Fast"),
	Average			UMETA(DisplayName = "Average"),
	AboveAverage	UMETA(DiaplayName = "Above Average"),
	Long			UMETA(DisplayName = "Long")
};

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class LUCIFERSHORDES_API UAbility : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		FName GetName() const { return this->Name; }
	UFUNCTION(BlueprintCallable)
		FName GetDevName() const { return this->devName; }
	UFUNCTION(BlueprintCallable)
		FText GetFluffDescription() const { return this->FluffDescription; }
	UFUNCTION(BlueprintCallable)
		FText GetEffectDescription() const { return this->EffectDescription; }
	UFUNCTION(BlueprintCallable)
		UTexture2D* GetIcon() const { return this->Icon; }

	UFUNCTION(BlueprintCallable)
		float GetMaxCoolDownTime() const { return this->CoolDownTime; }
	UFUNCTION(BlueprintCallable)
		float GetCoolDownTimer() const { return this->CD_Timer; }

	UAnimMontage* GetAnimMontage() const { return this->Montage; }

	FLH_GameplayEffect GetAbilityEffect() const { return this->Effect; }

	bool IsActive() const { return this->bIsActive; }

	//bool IsEffectApplied() const { return this->bEffectApplied; }

	AActor* GetOwner() const { return this->Owner; }

	void SetOwner(AActor* owner) { this->Owner = owner; }

	virtual void ExecuteAbility() PURE_VIRTUAL(UAbility::ExecuteAbility);

	virtual void Tick(float DeltaTime) PURE_VIRTUAL(UAbility::Tick);

	virtual void CoolDown(float DeltaTime) PURE_VIRTUAL(UAbility::CoolDown);

	virtual void Reset() PURE_VIRTUAL(UAbility::ResetCoolDownTime);

protected:
	UPROPERTY(EditDefaultsOnly)
		FName Name;
	UPROPERTY(EditDefaultsOnly)
		FName devName;
	UPROPERTY(EditDefaultsOnly)
		FText FluffDescription;
	UPROPERTY(EditDefaultsOnly)
		FText EffectDescription;
	UPROPERTY(EditDefaultsOnly)
		UTexture2D* Icon = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* Montage = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effect")
		FLH_GameplayEffect Effect;

	UPROPERTY(EditDefaultsOnly)
		/* 
		* Setting this to Custom uses the CoolDownTime property.
		* Fast: 5 seconds
		* Average: 10 seconds
		* Above Average: 15 seconds
		* Long: 25 seconds
		*/
		ECoolDownTier CoolDownTier = ECoolDownTier::Custom;

	UPROPERTY(EditDefaultsOnly)
		float CoolDownTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Tick")
		bool bCanTick = false;

	UPROPERTY(EditDefaultsOnly, Category = "Tick", meta = (ClampMin = 0.0f, ClampMax = 12.5f))
		float EffectTime = 0.0f;

	float CD_Timer = 0.0f;
	float E_Timer = 0.0f;

	bool bIsActive = false;
	//bool bEffectApplied = false;

	AActor* Owner;

};
