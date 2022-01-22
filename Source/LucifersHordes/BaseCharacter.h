//=====================================================
// Created By: Justin DaSilva
// Last Updated: 5/8/2021
//=====================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "DeathInterface.h"
#include "CombatInterface.h"
#include "EffectInterface.h"
#include "MeleeWeapon.h"
#include "Attributes.h"
#include "AbilityComponent.h"

#include "BaseCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams(FTakeDefaultDamageSignature, ABaseCharacter, OnTakeDefaultDamage, AActor*, DamagedActor, float, Damage, TArray<EDamageTypes>, DamageTypes, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS()
class LUCIFERSHORDES_API ABaseCharacter : public ACharacter, public ICombatInterface, public IDeathInterface, public IEffectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attacking")
		bool bIsAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Vitality")
		bool bIsDamaged;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vitality")
		bool bIsDying;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Vitality")
		bool bDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vitality")
		bool bIsInvincible;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vitality")
		float InvincibleTime;

	/************************** Delegates *******************************/
	UPROPERTY(BlueprintAssignable)
		FTakeDefaultDamageSignature OnTakeDefaultDamage;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAttributes* MyAttributes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAbilityComponent* AbililtyComponent;

	// The Current Weapon Equiped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		AMeleeWeapon* Equiped;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<AMeleeWeapon> StarterWeapon;

public:	/************************* FUNCTIONS ******************************/
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float TakeDefaultDamage(float DamageAmount, FDamageEvent const& DamageEvent, TArray<EDamageTypes> DamageTypes, AController* EventInstigator, AActor* DamageCauser);
	
	UAttributes* GetAttributesComponent() const { return this->MyAttributes; }
	void SetAttributesComponent(UAttributes* newAttributes) { MyAttributes = newAttributes; };

	AMeleeWeapon* GetEquipedWeapon() const { return this->Equiped; }

	void ActivateWeaponAbility();

	// temporarily public for now, move to statics eventually
	float PlayHighPriorityAnimMontage(UAnimMontage* HighPriorityMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);
	float TryToPlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Combat Interface
	int MeleeAttack_Implementation() override;
	bool AttackBegin_Implementation() override;
	bool IsAttacking_Implementation(FVector HitLocation) override;
	bool AttackEnd_Implementation() override;
	float GetCapsuleColliderRadius_Implementation() const override;
	int32 WhenDamaged_Implementation(AActor* DamageCauser) override;

	//Death interface
	int SetDie_Implementation() override;
	int Die_Implementation() override;

	// Effect Interface
	virtual void ApplyEffectToAttribute(FLH_GameplayEffect EffectToApply) override;
	// this does nothing its stupid
	virtual void AddTempDamageType(EDamageTypes DamageType) override;

};
