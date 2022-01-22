// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_TEST.h"
#include "LH_GameplayStatics.h"
#include "EffectInterface.h"

void UAbility_TEST::ExecuteAbility()
{
	this->bIsActive = true;

	// Apply Effect
	IEffectInterface* iEffect = Cast<IEffectInterface>(this->GetOwner());
	if (iEffect && !this->bCanTick)
	{
		iEffect->ApplyEffectToAttribute(this->GetAbilityEffect());
		//this->bEffectApplied = true;
	}

	// Add Damge Type Temporarily
	if (this->Effect.bIsTemporary && this->Effect.DamageType != EDamageTypes::None)
	{
		if (iEffect)
			iEffect->AddTempDamageType(this->Effect.DamageType);
	}
}

// called every frame by Ability component
void UAbility_TEST::Tick(float DeltaTime)
{
	// handle tick abilities
	if (this->IsActive() && this->bCanTick)
	{
		// if the timer is or exceeds the time then stop applying the effect
		static float counter = 0.0f;

		this->E_Timer += DeltaTime;

		if (this->E_Timer >= this->EffectTime)
			counter  = 0.0f;
		else if ((counter - (this->E_Timer - 1.0f)) <= 0.0f) // only apply the effect every second
		{
			// Apply Effect
			IEffectInterface* iEffect = Cast<IEffectInterface>(this->GetOwner());
			if (iEffect)
			{
				iEffect->ApplyEffectToAttribute(this->GetAbilityEffect());
			}

			counter = this->E_Timer;
		}
	}

	this->CoolDown(DeltaTime);
}

void UAbility_TEST::CoolDown(float DeltaTime)
{
	if (this->IsActive())
		this->CD_Timer -= DeltaTime;

	if (this->CD_Timer <= 0.0f)
		this->Reset();
}

void UAbility_TEST::Reset()
{
	if (this->bIsActive)
	{
		this->bIsActive = false;
		this->E_Timer = 0.0f;
		//this->bEffectApplied = false;
	}


	// Reset Damage Type
	if (this->Effect.bIsTemporary && this->Effect.DamageType != EDamageTypes::None)
	{
		auto IEffect = Cast<IEffectInterface>(this->GetOwner());
		if (IEffect)
			IEffect->AddTempDamageType(EDamageTypes::None);
	}

	// Reset Timer
	switch (this->CoolDownTier)
	{
		case ECoolDownTier::Custom:
		{
			this->CD_Timer = this->CoolDownTime;
			break;
		}
		case ECoolDownTier::Fast:
		{
			this->CD_Timer = this->CoolDownTime = 5.0f;
			break;
		}
		case ECoolDownTier::Average:
		{
			this->CD_Timer = this->CoolDownTime = 10.0f;
			break;
		}
		case ECoolDownTier::AboveAverage:
		{
			this->CD_Timer = this->CoolDownTime = 12.5f;
			break;
		}
		case ECoolDownTier::Long:
		{
			this->CD_Timer = this->CoolDownTime = 20.0f;
			break;
		}
	}
}