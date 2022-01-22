// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomEncounter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void ARoomEncounter::FinishedEncounter()
{
	bCompleted = true;
	for (int i = 0; i < Doors.Num(); i++) {
		Doors[i]->UnlockDoor();
	}
	if (ItemtoRequest != EItemType::None) {
		ItemSpawner->SpawnItem(ItemSpawnLocation->GetComponentLocation(), ItemtoRequest);
	}
	else {
		ItemSpawner->SpawnItem(ItemSpawnLocation->GetComponentLocation());
	}
	if (EncounterMatInstance)
		EncounterMatInstance->SetVectorParameterValue(TEXT("NewColor"), FLinearColor(1, 1, 1, 1));
	if (RoomCompleteAC)
		RoomCompleteAC->Play(0.0f);
}

// Sets default values
ARoomEncounter::ARoomEncounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!DummyComp) {
		DummyComp = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy Object"));
		RootComponent = DummyComp;
	}

	if (!EncounterCollision) {
		EncounterCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EncounterCollision"));

		EncounterCollision->BodyInstance.SetCollisionProfileName(TEXT("DoorCollider"));

		EncounterCollision->OnComponentBeginOverlap.AddDynamic(this, &ARoomEncounter::OnOverlapBegin);

		EncounterCollision->SetupAttachment(RootComponent);
	}

	if (!RoomSpace) {
		RoomSpace = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomSpace"));

		RoomSpace->BodyInstance.SetCollisionProfileName(TEXT("DoorCollider"));

		RoomSpace->OnComponentBeginOverlap.AddDynamic(this, &ARoomEncounter::FindRoomComponents);

		RoomSpace->SetupAttachment(RootComponent);
	}

	if (!ItemSpawnLocation) {
		ItemSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Item Spawn Location"));

		ItemSpawnLocation->SetupAttachment(RootComponent);
	}
	if (!EncounterSprite) {
		EncounterSprite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Encounter Sprite"));
		EncounterSprite->SetupAttachment(RootComponent);
	}
	if (!RoomCompleteAC) {
		RoomCompleteAC = CreateDefaultSubobject<UAudioComponent>(TEXT("RoomCompleteAC"));
		RoomCompleteAC->SetupAttachment(RootComponent);
	}

}

// Called when the game starts or when spawned
void ARoomEncounter::BeginPlay()
{
	Super::BeginPlay();

	bCompleted = false;

	RoomSpaceSize = this->GetActorLocation();
	this->SetActorLocation(FVector(RoomSpaceSize.X, RoomSpaceSize.Y, 5000),true);
	if(EncounterSprite)
		EncounterMatInstance = EncounterSprite->CreateAndSetMaterialInstanceDynamic(0);

	if(EncounterMatInstance)
		EncounterMatInstance->SetVectorParameterValue(TEXT("NewColor"), FLinearColor(0,0,0,1));

	TArray<AActor*> ItemSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawner::StaticClass(), ItemSpawners);

	if (ItemSpawners.Num() > 0) {
		ItemSpawner = CastChecked<AItemSpawner>(ItemSpawners[0]);
	}

	Target = 0;
	TotalDead = 0;
}

// Called every frame
void ARoomEncounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bMoved) {
		this->SetActorLocation(RoomSpaceSize, true);
		bMoved = true;
	}
}

int ARoomEncounter::Entered()
{
	for (int i = 0; i < enemySpawners.Num(); i++) {
		enemySpawners[i]->SpawnEnemies();
	}
	return 0;
}

int ARoomEncounter::Spawned_Implementation()
{
	Target++;
	return 0;
}


int ARoomEncounter::Died_Implementation()
{
	TotalDead++;
	if (TotalDead == Target) {
		FinishedEncounter();
	}
	return 0;
}

void ARoomEncounter::OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag("Player")) {
		return;
	}
	if (!bCompleted) {
		for (int i = 0; i < enemySpawners.Num(); i++) {
			enemySpawners[i]->SpawnEnemies();
		}
		for (int i = 0; i < Doors.Num(); i++) {
			Doors[i]->LockDoor();
		}
		if (EncounterMatInstance)
			EncounterMatInstance->SetVectorParameterValue(TEXT("NewColor"), FLinearColor(0.2, 0.2, 0.2, 1));
	}
}

void ARoomEncounter::FindRoomComponents(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor->ActorHasTag("LockingDoor")) {
		ALockingDoor* NewDoor = CastChecked<ALockingDoor>(OtherActor);
		if (NewDoor != nullptr && !Doors.Contains(NewDoor)) {
			Doors.Add(NewDoor);
			NewDoor->UnlockDoor();
		}
	}
	else if (OtherActor->ActorHasTag("EnemySpawner")) {
		AEnemySpawnPoint* NewSpawner = CastChecked<AEnemySpawnPoint>(OtherActor);
		if (NewSpawner != nullptr && !enemySpawners.Contains(NewSpawner)) {
			enemySpawners.Add(NewSpawner);
			NewSpawner->RoomPointer = this;
		}
	}
}