// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnemyMeleeWeapon.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUCIFERSHORDES_API UEnemyMeleeWeapon : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMeleeWeapon();
	   
	UCapsuleComponent* GetMyCapsuleComponent() const; 
protected:

	UPROPERTY(EditAnywhere, category = "Weapon", meta = (AllowProtectedAccess = "true"))
		UCapsuleComponent* MyCollider;

	UPROPERTY(EditDefaultsOnly, category = "Weapon")
		float DamageValue;
	


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

};
