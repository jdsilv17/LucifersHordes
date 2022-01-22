// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAI.h"

// Sets default values
ABaseEnemyAI::ABaseEnemyAI()
{
 
	/*Initialize the Pawn Senses*/
	if (!PawnSensingComp) {
		PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
		PawnSensingComp->SetPeripheralVisionAngle(90.0f);
	}

	//Collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	if (!HealthComp) {
		HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	}
	/*MySpawn = nullptr;*/
}

// Called when the game starts or when spawned
void ABaseEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
	/*if the the Ai catches the player then we can call the OnPlayerCaught Function*/
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ABaseEnemyAI::OnPlayerCaught);
	}

	TArray<AActor*> DoorSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorSpawner::StaticClass(), DoorSpawners);

	if (DoorSpawners.Num() > 0) {
		ADoorSpawner* DoorSpawner = CastChecked<ADoorSpawner>(DoorSpawners[0]);

		DoorSpawner->AddEnemy();

		this->OnDestroyed.AddDynamic(this, &ABaseEnemyAI::OnDestroy);
	}
}


// Called to bind functionality to input
void ABaseEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//Function that deals with the AI's health when it takes damage 
//void AAIDemonPatrol::DamageTaken(float damage)
//{
//
//	/*Subtract the Currhealth from health to get my Current Health*/
//	CurrHealth = CurrHealth - damage;
//
//	/*Checks to see if the current health is below or equal to zero*/
//	if (CurrHealth <= 0)
//	{
//		this->UnPossessed();
//	}
//}
//Function that will deal with the AI receiving damage
//void AAIDemonPatrol::GetHit()
//{
//	DamageTaken(25.0); 
//}

void ABaseEnemyAI::OnPlayerCaught(APawn* Pawn)
{
	/*Get a refernce to the player controller*/
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController()); 

	if (AIController)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You have been seen!"));
		AIController->SetPlayerCaught(Pawn); 
	}

}

void ABaseEnemyAI::OnDestroy(AActor* Act)
{
	TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorSpawner::StaticClass(), Targets);

	if (Targets.Num() > 0) {

		ADoorSpawner* DoorSpawner = CastChecked<ADoorSpawner>(Targets[0]);

		DoorSpawner->RemoveEnemy();
	}

	Targets.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawner::StaticClass(), Targets);

	if (Targets.Num() > 0) {


		AItemSpawner* ItemSpawner = CastChecked<AItemSpawner>(Targets[0]);
		check(ItemSpawner != nullptr);
		FBox boundBox = GetComponentsBoundingBox();

		ItemSpawner->SpawnItem(GetTransform().GetLocation());
	}
}
