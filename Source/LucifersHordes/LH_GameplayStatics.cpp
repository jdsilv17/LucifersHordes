// Fill out your copyright notice in the Description page of Project Settings.


#include "LH_GameplayStatics.h"

float ULH_GameplayStatics::ApplyDamage_(ABaseCharacter* DamagedCharacter, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass, TArray<EDamageTypes> DamageTypes)
{
	if (DamagedCharacter && (BaseDamage != 0.f))
	{
		// make sure we have a good damage type
		TSubclassOf<UDamageType> const ValidDamageTypeClass = DamageTypeClass ? DamageTypeClass : TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		return DamagedCharacter->TakeDefaultDamage(BaseDamage, DamageEvent, DamageTypes, EventInstigator, DamageCauser);
	}

	return 0.f;
}