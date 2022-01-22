//=====================================================
// Created By: Justin DaSilva
// Last Updated: 5/8/2021
//=====================================================


#include "BaseCharacter.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->bIsAttacking = false;
	this->bIsDamaged = false;
	this->bIsDying = false;
	this->bDead = false;

	this->SetCanBeDamaged(true);
	this->bIsInvincible = false;
	this->InvincibleTime = 1.5f;

	if (!this->MyAttributes) 
	{
		this->MyAttributes = CreateDefaultSubobject<UAttributes>(TEXT("AttributesComp"));
	}

	if (!this->AbililtyComponent)
	{
		this->AbililtyComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComp"));
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!this->Equiped && this->StarterWeapon)
	{
		this->Equiped = GetWorld()->SpawnActor<AMeleeWeapon>(this->StarterWeapon);
	}

	this->SetCanBeDamaged(true);
	this->bIsInvincible = false;

	if (this->MyAttributes->GetCurrentHealth() <= 0.0f)
	{
		this->MyAttributes->SetCurrentHealth(this->MyAttributes->GetMaxHealth());
	}
	
	// Slot WeaponAbility so it is ready for use
	if (this->AbililtyComponent && this->GetEquipedWeapon()->TryGetAbility())
	{
		this->AbililtyComponent->AddAbility(this->GetEquipedWeapon()->TryGetAbility());
	}
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (this->bIsDamaged)
	//{
	//	if (this->bIsInvincible)
	//	{
	//		this->InvincibleTime -= DeltaTime;
	//		if (this->InvincibleTime <= 0.0f)
	//		{
	//			this->bIsInvincible = false;
	//			this->InvincibleTime = 1.5f;
	//		}
	//	}
	//}
	
	// if invincible then cant be damaged
	this->SetCanBeDamaged(!this->bIsInvincible);

}

float ABaseCharacter::TakeDefaultDamage(float DamageAmount, FDamageEvent const& DamageEvent, TArray<EDamageTypes> DamageTypes, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = DamageAmount;

	UDamageType const* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		// point damage event, pass off to helper function
		FPointDamageEvent* const PointDamageEvent = (FPointDamageEvent*)&DamageEvent;
		ActualDamage = InternalTakePointDamage(ActualDamage, *PointDamageEvent, EventInstigator, DamageCauser);

		// K2 notification for this actor
		if (ActualDamage != 0.f)
		{
			ReceivePointDamage(ActualDamage, DamageTypeCDO, PointDamageEvent->HitInfo.ImpactPoint, PointDamageEvent->HitInfo.ImpactNormal, PointDamageEvent->HitInfo.Component.Get(), PointDamageEvent->HitInfo.BoneName, PointDamageEvent->ShotDirection, EventInstigator, DamageCauser, PointDamageEvent->HitInfo);
			OnTakePointDamage.Broadcast(this, ActualDamage, EventInstigator, PointDamageEvent->HitInfo.ImpactPoint, PointDamageEvent->HitInfo.Component.Get(), PointDamageEvent->HitInfo.BoneName, PointDamageEvent->ShotDirection, DamageTypeCDO, DamageCauser);

			// Notify the component
			UPrimitiveComponent* const PrimComp = PointDamageEvent->HitInfo.Component.Get();
			if (PrimComp)
			{
				PrimComp->ReceiveComponentDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
			}
		}
	}
	else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		// radial damage event, pass off to helper function
		FRadialDamageEvent* const RadialDamageEvent = (FRadialDamageEvent*)&DamageEvent;
		ActualDamage = InternalTakeRadialDamage(ActualDamage, *RadialDamageEvent, EventInstigator, DamageCauser);

		// K2 notification for this actor
		if (ActualDamage != 0.f)
		{
			FHitResult const& Hit = (RadialDamageEvent->ComponentHits.Num() > 0) ? RadialDamageEvent->ComponentHits[0] : FHitResult();
			ReceiveRadialDamage(ActualDamage, DamageTypeCDO, RadialDamageEvent->Origin, Hit, EventInstigator, DamageCauser);
			OnTakeRadialDamage.Broadcast(this, ActualDamage, DamageTypeCDO, RadialDamageEvent->Origin, Hit, EventInstigator, DamageCauser);

			// add any desired physics impulses to our components
			for (int HitIdx = 0; HitIdx < RadialDamageEvent->ComponentHits.Num(); ++HitIdx)
			{
				FHitResult const& CompHit = RadialDamageEvent->ComponentHits[HitIdx];
				UPrimitiveComponent* const PrimComp = CompHit.Component.Get();
				if (PrimComp && PrimComp->GetOwner() == this)
				{
					PrimComp->ReceiveComponentDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
				}
			}
		}
	}

	// generic damage notifications sent for any damage
	// note we will broadcast these for negative damage as well
	if (ActualDamage != 0.f)
	{
		ReceiveAnyDamage(ActualDamage, DamageTypeCDO, EventInstigator, DamageCauser);
		OnTakeDefaultDamage.Broadcast(this, ActualDamage, DamageTypes, EventInstigator, DamageCauser);
		if (EventInstigator != nullptr)
		{
			EventInstigator->InstigatedAnyDamage(ActualDamage, DamageTypeCDO, this, DamageCauser);
		}
	}

	return ActualDamage;
}

float ABaseCharacter::PlayHighPriorityAnimMontage(UAnimMontage* HighPriorityMontage, float InPlayRate, FName StartSectionName)
{
	float Duration = 0.0f;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (!AnimInstance->Montage_IsPlaying(HighPriorityMontage))
		Duration = PlayAnimMontage(HighPriorityMontage, InPlayRate, StartSectionName);

	return Duration;
}

float ABaseCharacter::TryToPlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	float Duration = 0.0f;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (!AnimInstance->IsAnyMontagePlaying())
		Duration = PlayAnimMontage(AnimMontage, InPlayRate, StartSectionName);

	return Duration;
}

void ABaseCharacter::ActivateWeaponAbility()
{
	// change this, need beter way to set ability
	if (!this->AbililtyComponent->bActivated && this->GetEquipedWeapon()->TryGetAbility())
	{
		this->AbililtyComponent->ActivateAbility(this->GetEquipedWeapon()->TryGetAbility()->GetName());
	}
}

int ABaseCharacter::MeleeAttack_Implementation()
{
	return 0;
}

bool ABaseCharacter::AttackBegin_Implementation()
{	
	//this->bIsAttacking = true;
	if (/*this->bIsAttacking && */this->Equiped && this->Equiped->GetParticleSystem())
	{
		this->Equiped->SetActorEnableCollision(true);
		return true;
	}
	return false;
}

bool ABaseCharacter::IsAttacking_Implementation(FVector HitLocation)
{
	if (/*this->bIsAttacking && */this->Equiped && this->Equiped->GetParticleSystem())
	{
		this->Equiped->SetHitLocation(HitLocation);
		return true;
	}
	return false;
}

bool ABaseCharacter::AttackEnd_Implementation()
{
	//if (this->bIsAttacking)
	{
		this->Equiped->SetActorEnableCollision(false);
		this->Equiped->EmptyActorIgnoreList();
		//this->bIsAttacking = false;
		return true;
	}
	return false;
}

float ABaseCharacter::GetCapsuleColliderRadius_Implementation() const
{
	float radius = 0.0;
	if (this->Equiped)
	{
		radius = this->Equiped->GetCapsuleComp()->GetUnscaledCapsuleRadius();
	}
	return radius;
}

int32 ABaseCharacter::WhenDamaged_Implementation(AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Damaged 1"));
	if (this->bIsDying)
		return 0;

	//if (!this->bIsInvincible)
	//{
	//	this->bIsInvincible = true;
	//	this->bIsDamaged = true;
	//}

	//FVector LaunchVel;
	//float launchInfluence = 1000.0f;
	////LaunchVel = -GetActorForwardVector() /** -10000.0f*/;
	//FVector MeToThem(DamageCauser->GetActorLocation() - GetActorLocation()); // GetLocation() temp function
	//MeToThem.Normalize();
	//FVector Dir(MeToThem.X, MeToThem.Y, 0.0f);
	//Dir.Normalize();
	//LaunchVel = FVector(-Dir.X * 100.0f, Dir.Y, 0.125f) * launchInfluence;

	//LaunchCharacter(LaunchVel, true, true);

	//AddMovementInput(LaunchVel, -1.0f);

	return this->bIsDamaged = true;
}

int ABaseCharacter::SetDie_Implementation()
{
	return 0;
}

int ABaseCharacter::Die_Implementation()
{
	return 0;
}

void ABaseCharacter::ApplyEffectToAttribute(FLH_GameplayEffect EffectToApply)
{
	this->GetAttributesComponent()->ApplyEffect(EffectToApply);
}

void ABaseCharacter::AddTempDamageType(EDamageTypes DamageType)
{
	Cast<IEffectInterface>(this->GetEquipedWeapon())->AddTempDamageType(DamageType);
}

