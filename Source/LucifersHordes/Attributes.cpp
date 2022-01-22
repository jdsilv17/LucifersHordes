// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes.h"
#include "BaseCharacter.h"
#include "LH_GameplayStatics.h"

// Sets default values for this component's properties
UAttributes::UAttributes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	this->CurrentHealth = this->MaxHealth = 100.0f;
	this->FireResistance = this->IceResistance = -0.15f;
}

void UAttributes::BeginPlay()
{
	Super::BeginPlay();

	this->CurrentHealth = this->MaxHealth;
	
	// might turn this into function
	auto character = Cast<ABaseCharacter>(this->GetOwner());

	if (character)
	{
		character->OnTakeDefaultDamage.AddDynamic(this, &UAttributes::OnTakeDefaultDamage);
		character->OnTakeAnyDamage.AddDynamic(this, &UAttributes::OnTakeAnyDamage);
	}
}

//void UAttributes::EndPlay(EEndPlayReason::Type end)
//{
//	Super::EndPlay(end);
//}

void UAttributes::ApplyEffect(FLH_GameplayEffect Effect)
{
	UUIManagerGameInstance* uiManager = Cast<UUIManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	for (auto Modifier : Effect.Modifiers)
	{
		switch (Modifier.AttributeToEffect)
		{
		case EAttributes::None:
			//Relics of this type have no effect on the attributes.
			break;
		case EAttributes::Health:
		{
			// possibly change this to ApplyDamage
			this->CurrentHealth = FMath::Clamp(this->CurrentHealth + Modifier.AttributeModifier, 0.0f, this->MaxHealth);
			break;
		}
		case EAttributes::MaxHealth:
		{
			//Relics of this type effect the attributes MaxHealth value.
			MaxHealth += Modifier.AttributeModifier;
			CurrentHealth += Modifier.AttributeModifier;
			uiManager->enduranceItemCount++;
			break;
		}
		case EAttributes::FireRes:
		{
			FireResistance += Modifier.AttributeModifier;
			uiManager->fireResistItemCount++;
			break;
		}
		case EAttributes::IceRes:
		{
			IceResistance += Modifier.AttributeModifier;
			uiManager->iceResistItemCount++;
			break;
		}
		case EAttributes::Lifesteal:
		{
			Lifesteal += Modifier.AttributeModifier;
			uiManager->lifestealItemCount++;
			break;
		}
		}
	}
}

void UAttributes::OnTakeAnyDamage
(
	AActor* DamagedActor,
	float Damage,
	const class UDamageType* DamageType,
	class AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (Damage <= 0)
		return;

	this->CurrentHealth = FMath::Clamp(this->CurrentHealth - Damage, 0.0f, this->MaxHealth);

	ICombatInterface* const iCombat = Cast<ICombatInterface>(this->GetOwner());
	if (Damage > 0.0f && iCombat)
		iCombat->Execute_WhenDamaged(this->GetOwner(), DamageCauser);

	if (this->CurrentHealth < 1.0f)
	{
		if (IDeathInterface* Dead = Cast<IDeathInterface>(this->GetOwner()))
		{
			Dead->Execute_SetDie(this->GetOwner());
		}
	}
}

void UAttributes::OnTakeDefaultDamage(AActor* DamagedActor, float Damage, TArray<EDamageTypes> DamageTypes, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0.0f)
		return;

	// Handle LifeSteal Damage
	if (DamageTypes.Contains(EDamageTypes::LifeStealFrom))
	{
		// Apply negative Damage multiplied by lifesteal value to the Damage Causer
		TArray<EDamageTypes> LifeStealTo;
		LifeStealTo.Add(EDamageTypes::LifeStealTo);
		ULH_GameplayStatics::ApplyDamage_(Cast<ABaseCharacter>(DamageCauser), Damage, this->GetOwner()->GetInstigatorController(), DamagedActor, NULL, LifeStealTo);
	}
	if (DamageTypes.Contains(EDamageTypes::LifeStealTo))
	{
		// Applies negative damage
		FLH_GameplayEffect heal;
		FModifier mod;
		mod.AttributeModifier = Damage * this->Lifesteal;
		mod.AttributeToEffect = EAttributes::Health;
		heal.Modifiers.Add(mod);
		this->ApplyEffect(heal);
		return;
	}

	auto size = DamageTypes.Num();
	for (int i = 0; i < size; ++i)
	{
		switch (DamageTypes[i])
		{
			case EDamageTypes::None:
				break;
			case EDamageTypes::Fire:
			{
				Damage -= Damage * this->FireResistance;
				break;
			}
			case EDamageTypes::Ice:
			{
				Damage -= Damage * this->IceResistance;
				break;
			}
			case EDamageTypes::Heal:
				break;
			case EDamageTypes::LifeStealTo:
				break;
			case EDamageTypes::LifeStealFrom:
				break;
		}
	}

	Damage = FMath::Max(0.0f, Damage);
	this->CurrentHealth = FMath::Clamp(this->CurrentHealth - Damage, 0.0f, this->MaxHealth);

	ICombatInterface* const iCombat = Cast<ICombatInterface>(this->GetOwner());
	if (Damage > 0.0f && iCombat)
		iCombat->Execute_WhenDamaged(this->GetOwner(), DamageCauser);

	if (this->CurrentHealth < 1.0f)
	{
		if (IDeathInterface* Dead = Cast<IDeathInterface>(this->GetOwner()))
		{
			Dead->Execute_SetDie(this->GetOwner());
		}
	}
}
