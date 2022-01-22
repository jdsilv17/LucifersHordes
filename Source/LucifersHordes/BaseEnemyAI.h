// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Unreal
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"


//Ours
#include "EnemyAIController.h"
#include "HealthComponent.h"
#include "EnemySpawnPoint.h"
#include "DoorSpawner.h"
#include "ItemSpawner.h"


#include "BaseEnemyAI.generated.h"

UCLASS()
class LUCIFERSHORDES_API ABaseEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//the function that will make the AI do damage when it runs into the player. 
	//void ImpactDamage(); 
public:	
	
	/*Health variable*/
	/*UPROPERTY(EditAnywhere); 
	float CurrHealth; 

	const float MaxHealth = 100.0f; */
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree; 

	/*What gives the ai vision*/
	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSensingComp; 

	//HealthComp
	UPROPERTY(EditDefaultsOnly, Category = Health)
		UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, Category = Spawnpoint)
		AEnemySpawnPoint* MySpawn;

private:
	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);

	UFUNCTION()
		void OnDestroy(AActor* Act);
};
