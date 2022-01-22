//=====================================================
// Author: Justin DaSilva, Christian Chincilla, Kurtis McCammon
// Last Updated: 4/15/2021
//=====================================================


#include "HealthComponent.h"
#include "GameFramework/Actor.h"

#include "DeathInterface.h"
#include "CombatInterface.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	CurrentHealth = MaxHealth = 100.0f;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	this->CurrentHealth = this->MaxHealth;

	//if (this->GetOwner())
	//	this->GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage
(
	AActor* DamagedActor, 
	float Damage, 
	const class UDamageType* DamageType, 
	class AController* InstigatedBy, 
	AActor* DamageCauser	)
{
	if (Damage <= 0)
		return;

	ICombatInterface* const iCombat = Cast<ICombatInterface>(this->GetOwner()); 

	this->CurrentHealth = FMath::Clamp(this->CurrentHealth - Damage, 0.0f, this->MaxHealth);

	iCombat->Execute_WhenDamaged(this->GetOwner(), DamageCauser);

	if (this->CurrentHealth <= 0.0f)
	{
		if (IDeathInterface* Dead = Cast<IDeathInterface>(this->GetOwner()))
		{
			Dead->Execute_SetDie(this->GetOwner());
		}
	}
}

