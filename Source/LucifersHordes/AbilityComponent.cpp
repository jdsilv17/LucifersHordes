// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "BaseCharacter.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->bActivated = false;
	this->ActiveAbility = nullptr;
	this->bEffectApplied = false;
	this->SlottedAbilities.Empty();
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	this->bActivated = false;
	this->bEffectApplied = false;
	this->SlottedAbilities.Reset();
}

// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto pair : this->SlottedAbilities)
	{
		auto ability = pair.Value;
		if (ability && ability->IsActive())
		{
			if (!Cast<ACharacter>(this->GetOwner())->GetMesh()->GetAnimInstance()->Montage_IsPlaying(ability->GetAnimMontage()))
				this->bActivated = false;

			// Ability Tick
			ability->Tick(DeltaTime);

			// Ability is no longer active
			if (!ability->IsActive() && this->bEffectApplied)
			{
				// if the ability's effect is temporary undo the effect after cooldown
				if (ability->GetAbilityEffect().bIsTemporary)
				{
					FLH_GameplayEffect undo;
					size_t size = ability->GetAbilityEffect().Modifiers.Num();
					for (size_t i = 0; i < size; ++i)
					{
						FModifier mod;
						mod.AttributeToEffect = ability->GetAbilityEffect().Modifiers[i].AttributeToEffect;
						mod.AttributeModifier = -ability->GetAbilityEffect().Modifiers[i].AttributeModifier;
						undo.Modifiers.Add(mod);
					}
					IEffectInterface* iEffect = Cast<IEffectInterface>(this->GetOwner());
					if (iEffect)
						iEffect->ApplyEffectToAttribute(undo);
				}

				// reset
				this->bEffectApplied = false;
			}
		}
	}
}

void UAbilityComponent::ActivateAbility(FName Key)
{
	// if no ability has been slotted then do nothing
	// put warning message
	auto ability = this->SlottedAbilities[Key];
	if (!ability) return;

	this->bActivated = true;

	if (!ability->IsActive())
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(this->GetOwner());
		if (character)
		{
			// Play Ability Montage
			UAnimMontage* montage = ability->GetAnimMontage();
			if (montage)
			{
				character->PlayHighPriorityAnimMontage(montage, 1.0f);

				// Execute Ability
				ability->ExecuteAbility();
				this->bEffectApplied = true;
			}
		}
	}
}

void UAbilityComponent::AddAbility(UAbility* ability)
{
	if (ability)
	{
		ability->SetOwner(this->GetOwner());
		ability->Reset();
		this->SlottedAbilities.Add(ability->GetName(), ability);
	}
}

void UAbilityComponent::AddPAbility(UAbility* ability)
{
	if (ability)
	{
		ability->SetOwner(this->GetOwner());
		ability->Reset();
		this->SlottedAbilities.Add(ability->GetDevName(), ability);
	}
}

void UAbilityComponent::RemoveAbility(FName Key)
{
	//this->SlottedAbilities.FindAndRemoveChecked(Key);
	this->SlottedAbilities.Remove(Key);
}

