// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
//#include "GameFramework/Character.h"

//#include "Animation/AnimMontage.h"
//#include "CombatInterface.h"
//#include "EnemyMeleeWeapon.h"
//#include "DeathInterface.h"

#include "BaseCharacter.h"
#include "UIManagerGameInstance.h"
#include "RoomManagerInterface.h"

#include "RootEnemyCharacter.generated.h"

UCLASS()
class LUCIFERSHORDES_API ARootEnemyCharacter : public ABaseCharacter/*public ACharacter, public ICombatInterface, public IDeathInterface*/
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARootEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int MeleeAttack_Implementation() override;

	int SetDie_Implementation() override;

	int Die_Implementation() override;

	int WhenDamaged_Implementation(AActor* DamageCauser) override;

	//bool AttackBegin_Implementation() override; 

	//bool IsAttacking_Implementation(FVector HitLocation)override;

	//bool AttackEnd_Implementation() override;

	//float GetCapsuleColliderRadius_Implementation() const override; 

	UAnimMontage* getMontage() const;

	UAnimMontage* getDeathMontage() const;

	void SetOrigin(FVector newOrgin);

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Death")
	//	bool bDead;

	bool bAttacking;

	void notifyRoom();
	UPROPERTY(EditAnywhere)
		TScriptInterface<IRoomManagerInterface> RoomPointer;

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//	UEnemyMeleeWeapon* MyMeleeWeapon;
	//
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	//	UHealthComponent* HealthComp;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
		UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
		UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
		UAnimMontage* DamageMontage;

	FVector Origin;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
		float DecayTime;
};
