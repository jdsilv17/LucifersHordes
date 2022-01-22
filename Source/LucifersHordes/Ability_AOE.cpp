// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_AOE.h"
#include "EffectInterface.h"
#include "LH_GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

class ABaseCharacter;

void UAbility_AOE::ExecuteAbility()
{
	// change how this works
	this->bIsActive = true;

	// Apply Effect
	IEffectInterface* iEffect = Cast<IEffectInterface>(this->GetOwner());
	if (iEffect)
	{
		iEffect->ApplyEffectToAttribute(this->GetAbilityEffect());

		// Do AOE attack
		TArray<AActor*> ignoreList;
		ignoreList.Add(this->GetOwner());
		TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
		objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
		TArray<AActor*> outActors;

		//UKismetSystemLibrary::DrawDebugSphere(this->GetOwner()->GetWorld(), this->GetOwner()->GetActorLocation(), this->Radius, 16, FColor::Red, 10.0f);
		bool hit = UKismetSystemLibrary::SphereOverlapActors(this->GetOwner()->GetWorld(), this->GetOwner()->GetActorLocation(), this->Radius, objectTypes, nullptr, ignoreList, outActors);
		if (hit)
		{
			TArray<EDamageTypes> damageTypes;
			damageTypes.Add(this->GetAbilityEffect().DamageType);
			for (auto actor : outActors)
			{
				auto character = Cast<ABaseCharacter>(actor);

				// Launch Character
				FVector themToMe(this->GetOwner()->GetActorLocation() - character->GetActorLocation()); // GetLocation() temp function
				themToMe.Normalize();
				FVector Dir(themToMe.X, themToMe.Y, 0.0f);
				Dir.Normalize();

				FVector launchVel = FVector(-Dir.X * 1.3f, -Dir.Y, 1.0f) * this->LaunchInfluence;
				if (launchVel.IsNearlyZero()) 
					launchVel = FVector::OneVector * this->LaunchInfluence;

				character->GetCharacterMovement()->StopActiveMovement();
				character->GetCharacterMovement()->Launch(launchVel);
				character->GetCharacterMovement()->HandlePendingLaunch();

				// Apply Damage to character
				ULH_GameplayStatics::ApplyDamage_(character, this->DamageToApply, this->GetOwner()->GetInstigatorController(), this->GetOwner(), NULL, damageTypes);
			}
		}
	}

	// Add Damge Type Temporarily
	if (this->Effect.bIsTemporary && this->Effect.DamageType != EDamageTypes::None)
	{
		if (iEffect)
			iEffect->AddTempDamageType(this->Effect.DamageType);
	}
}

void UAbility_AOE::Tick(float DeltaTime)
{
	// handle tick abilities
	if (this->IsActive())
	{
		if (this->bCanTick)
		{
			// if the timer is or exceeds the time then stop applying the effect
			//static float counter = 0.0f;

			//this->E_Timer += DeltaTime;

			//if (this->E_Timer >= this->EffectTime)
			//	counter = 0.0f;
			//else if ((counter - (this->E_Timer - 1.0f)) <= 0.0f) // only apply the effect every second
			//{
			//	// Apply Effect
			//	IEffectInterface* iEffect = Cast<IEffectInterface>(this->GetOwner());
			//	if (iEffect)
			//	{
			//		iEffect->ApplyEffectToAttribute(this->GetAbilityEffect());
			//	}

			//	counter = this->E_Timer;
			//}

			if (Cast<ACharacter>(this->GetOwner())->GetMesh()->GetAnimInstance()->Montage_IsPlaying(this->GetAnimMontage()))
			{
				// Do AOE attack
				TArray<AActor*> ignoreList;
				ignoreList.Add(this->GetOwner());
				TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
				objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
				TArray<AActor*> outActors;

				//UKismetSystemLibrary::DrawDebugSphere(this->GetOwner()->GetWorld(), this->GetOwner()->GetActorLocation(), this->Radius, 16, FColor::Red, 10.0f);
				bool hit = UKismetSystemLibrary::SphereOverlapActors(this->GetOwner()->GetWorld(), this->GetOwner()->GetActorLocation(), this->Radius, objectTypes, nullptr, ignoreList, outActors);
				if (hit)
				{
					for (auto actor : outActors)
					{
						auto character = Cast<ABaseCharacter>(actor);

						// Launch Character
						FVector themToMe(this->GetOwner()->GetActorLocation() - character->GetActorLocation()); // GetLocation() temp function
						themToMe.Normalize();
						FVector Dir(themToMe.X, themToMe.Y, 0.0f);
						Dir.Normalize();

						FVector launchVel = FVector(-Dir.X * 1.3f, -Dir.Y, 1.0f) * this->LaunchInfluence;
						if (launchVel.IsNearlyZero())
							launchVel = FVector::OneVector * this->LaunchInfluence;

						character->GetCharacterMovement()->StopActiveMovement();
						character->GetCharacterMovement()->Launch(launchVel);
						character->GetCharacterMovement()->HandlePendingLaunch();
					}
				}
			}
		}
	}

	this->CoolDown(DeltaTime);
}

void UAbility_AOE::CoolDown(float DeltaTime)
{
	if (this->IsActive())
		this->CD_Timer -= DeltaTime;

	if (this->CD_Timer <= 0.0f)
		this->Reset();
}

void UAbility_AOE::Reset()
{
	if (this->bIsActive)
	{
		this->bIsActive = false;
		this->E_Timer = 0.0f;
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
