// Fill out your copyright notice in the Description page of Project Settings.


#include "RootEnemyCharacter.h"
#include "RootEnemyController.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "HealthComponent.h"

// Sets default values
ARootEnemyCharacter::ARootEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->bUseControllerRotationYaw = false;

	//this->GetCharacterMovement()->bUseControllerDesiredRotation = true;
	this->GetCharacterMovement()->bOrientRotationToMovement = true;

	this->GetCharacterMovement()->bUseRVOAvoidance = true;
}

void ARootEnemyCharacter::notifyRoom()
{
	RoomPointer->Execute_Spawned(RoomPointer.GetObject());
}

// Called when the game starts or when spawned
void ARootEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*TArray<AActor*> DoorSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorSpawner::StaticClass(), DoorSpawners);

	if (DoorSpawners.Num() > 0) {
		ADoorSpawner* DoorSpawner = CastChecked<ADoorSpawner>(DoorSpawners[0]);

		DoorSpawner->AddEnemy();
	}*/

	if (this->Equiped && this->StarterWeapon)
	{
		this->Equiped->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftHandSocket"));
	}

	this->GetCharacterMovement()->bUseRVOAvoidance = true;
}

// Called every frame
void ARootEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->GetMovementComponent()->IsFalling() 
		&& this->GetMesh()->GetAnimInstance()->Montage_IsPlaying(this->DamageMontage))
		StopAnimMontage(this->DamageMontage);
	if (this->bIsDamaged && !this->GetMovementComponent()->IsFalling())
		this->bIsDamaged = false;

	if (bDead) {
		DecayTime -= DeltaTime;
		if (DecayTime <= 0)
		{
			Destroy();
		}
	}
}

int ARootEnemyCharacter::MeleeAttack_Implementation()
{
	if (this->Montage)
	{
		TryToPlayAnimMontage(this->Montage);
	}
	return 0;
}

//bool ARootEnemyCharacter::AttackBegin_Implementation()
//{
//	if (this->bAttacking)
//	{
//		this->MyMeleeWeapon->GetMyCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//		return true;
//	}
//	return false;
//}
//
//bool ARootEnemyCharacter::IsAttacking_Implementation(FVector HitLocation)
//{
//	if (this->bIsAttacking)
//	{ 
//		this->MyMeleeWeapon->GetMyCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//		return true;
//	}
//	return false; 
//}
//
//bool ARootEnemyCharacter::AttackEnd_Implementation()
//{
//	if (this->bIsAttacking)
//	{
//		this->MyMeleeWeapon->GetMyCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//		return false; 
//	}
//	return false; 
//}
//
//float ARootEnemyCharacter::GetCapsuleColliderRadius_Implementation() const
//{
//	float raidus = 0.0f; 
//	if (this->MyMeleeWeapon)
//	{
//		raidus = this->MyMeleeWeapon->GetMyCapsuleComponent()->GetUnscaledCapsuleRadius(); 
//	}
//	return raidus;
//}

int ARootEnemyCharacter::WhenDamaged_Implementation(AActor* DamageCauser)
{
	this->bIsDamaged = true;
	if (this->DamageMontage && !this->GetMovementComponent()->IsFalling())
	{
		//StopAnimMontage(this->Montage); 
		PlayHighPriorityAnimMontage(this->DamageMontage);
	}

	return 0;
}

int ARootEnemyCharacter::SetDie_Implementation()
{
	ARootEnemyController* cont = Cast<ARootEnemyController>(GetController());
	
	cont->get_Blackboard()->SetValueAsBool(BB_Keys::IAmDead, true);

	this->GetCharacterMovement()->bUseRVOAvoidance = false;

	return 0;
}

int ARootEnemyCharacter::Die_Implementation()
{
	/*if (this->DeathMontage)
	{
		PlayAnimMontage(this->DeathMontage, 2.0f);
	}*/
	/*TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorSpawner::StaticClass(), Targets);

	if (Targets.Num() > 0) {

		ADoorSpawner* DoorSpawner = CastChecked<ADoorSpawner>(Targets[0]);

		DoorSpawner->RemoveEnemy();
	}*/

	/*Targets.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawner::StaticClass(), Targets);

	if (Targets.Num() > 0) {


		AItemSpawner* ItemSpawner = CastChecked<AItemSpawner>(Targets[0]);
		check(ItemSpawner != nullptr);
		FBox boundBox = GetComponentsBoundingBox();

		ItemSpawner->SpawnItem(GetTransform().GetLocation());
	}*/
	SetActorEnableCollision(false);

	this->Equiped->Destroy();

	if (RoomPointer) {
		RoomPointer->Execute_Died(RoomPointer.GetObject());
	}


	//Update kill count
	UUIManagerGameInstance* uiManager = Cast<UUIManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	uiManager->totalKillCount++;
	uiManager->globalKillCount++;

	//Increases player's silver amount per kill
	uiManager->silverCount += 15;

	//Update kill counts for specific weapon challenges
	if (uiManager->weapon != NULL)
	{
		if (uiManager->weapon->Name.ToString().Contains("dagger"))
		{
			uiManager->daggerKillCount++;
			uiManager->tempDaggerKills++;
		}
		else if (uiManager->weapon->Name.ToString().Contains("sword"))
		{
			uiManager->swordKillCount++;
			uiManager->tempSwordKills++;
		}
		else if (uiManager->weapon->Name.ToString().Contains("hammer"))
		{
			uiManager->hammerKillCount++;
			uiManager->tempHammerKills++;
		}
		else if (uiManager->weapon->Name.ToString().Contains("bag"))
		{
			uiManager->breadKillCount++;
			uiManager->tempBreadKills++;
		}
		else if (uiManager->weapon->Name.ToString().Contains("morning"))
		{
			uiManager->morningKillCount++;
			uiManager->tempMorningKills++;
		}
		else
		{
			//Do Nothing
		}
	}

	bDead = true;
	return 0;
}

UAnimMontage* ARootEnemyCharacter::getMontage() const
{
	return this->Montage;
}

UAnimMontage* ARootEnemyCharacter::getDeathMontage() const
{
	return this->DeathMontage;
}

void ARootEnemyCharacter::SetOrigin(FVector newOrigin)
{
	Origin = newOrigin;
}