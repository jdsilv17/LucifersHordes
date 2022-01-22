//=====================================================
// Modified By: Kurtis McCammon, Justin DaSilva
// Last Updated: 5/8/2021
//=====================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Ability.h"
#include "Effectinterface.h"

#include "MeleeWeapon.generated.h"

class UCapsuleComponent;
class UParticleSystemComponent;
class USoundCue;
class UAudioComponent;
class ULH_WeaponAsset;


UCLASS()
class LUCIFERSHORDES_API AMeleeWeapon : public AActor, public IEffectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

	UFUNCTION(BlueprintCallable)
		UStaticMeshComponent* GetMesh();

	UParticleSystem* GetParticleSystem() const { return this->HitEffect; }

	UCapsuleComponent* GetCapsuleComp() const { return this->MyWeaponCollider; }

	TArray<UAnimMontage*> GetPrimaryAttackAnims() const { return this->PrimaryAttackAnims; }

	TArray<UAnimMontage*> GetSecondaryAttackAnims() const { return this->SecondaryAttackAnims; }

	float GetAttackSpeed() const { return this->attackSpeedModifier; }

	// Returns the Ability attached to the weapon if there is one
	UFUNCTION(BlueprintCallable)
		UAbility* TryGetAbility() const;

	void EmptyActorIgnoreList() { this->ActorIgnoreList.Empty(); }

	void SetHitLocation(FVector location) { this->HitLocation = location; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Info")
		FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Info")
		FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Info")
		FText Modifiers;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Info")
		FText Values;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Info")
		UTexture2D* Icon;

	void SetAbility(TSubclassOf<UAbility> newAbility);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USceneComponent* dummy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Asset")
		ULH_WeaponAsset* WeaponData;
	UPROPERTY(EditDefaultsOnly, Category = WeaponSettings) 
		UStaticMeshComponent* MyMesh;
	UPROPERTY(EditDefaultsOnly, Category = WeaponSettings)
		UCapsuleComponent* MyWeaponCollider;

	UPROPERTY(EditDefaultsOnly, Category = WeaponSettings)
		TArray<EDamageTypes> DamageTypes;
	UPROPERTY(EditDefaultsOnly, Category = WeaponSettings)
		float DamageValue;
	UPROPERTY(EditDefaultsOnly, Category = WeaponSettings)
		float attackSpeedModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponSettings)
		TSubclassOf<UAbility> Ability;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
		UParticleSystemComponent* PSC;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particles")
		UParticleSystemComponent* HitPSC;
	UPROPERTY(EditDefaultsOnly, Category = "Particles")
		UParticleSystem* HitEffect;

	// change this to be more generic
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		USoundCue* BloodyBladeCue;

	UAudioComponent* BloodyBladeAC;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
		TArray<UAnimMontage*> PrimaryAttackAnims;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
		TArray<UAnimMontage*> SecondaryAttackAnims;


	UFUNCTION()
		void OnOverlapBegin
		(
			UPrimitiveComponent* OverLapComp, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, 
			bool bFromSweep, 
			const FHitResult& SweepResult
		);

private:
	TArray<AActor*> ActorIgnoreList;
	FVector HitLocation;
	FTimerHandle UnusedHandle;
	int hitCount = 0;

	void ResetTime();

	// Effect Interface
	// this does nothing its stupid
	virtual void ApplyEffectToAttribute(FLH_GameplayEffect EffectToApply) override;
	virtual void AddTempDamageType(EDamageTypes DamageType) override;
};
