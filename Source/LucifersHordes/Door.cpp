// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!Root)
	{
		Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
		RootComponent = Root;
	}

	if (!BoxCollider) {
		BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));

		BoxCollider->BodyInstance.SetCollisionProfileName(TEXT("DoorCollider"));

		BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);

		BoxCollider->SetupAttachment(RootComponent);
	}

	if (!DoorMesh) {
		DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
		check(DoorMesh != nullptr);

		DoorMesh->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	delay = 5.0f;
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(this->delay-=DeltaTime <= 0)
		this->bReady = true;

}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (this->bReady && OtherActor->ActorHasTag(FName(TEXT("Player")))) {
		DoorOpened();

	}
}

void ADoor::DoorOpened()
{
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), TargetWorldName);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Teleported."));
	
	FString levelName = TargetWorldName.ToString();
	if (levelName.Contains("limbo"))
	{
		UUIManagerGameInstance* lhGameManager = Cast<UUIManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		lhGameManager->currLevelsCleared++;
		lhGameManager->globalLevelsCleared++;
	}
}

void ADoor::SetTargetWorld(FName newName)
{
	TargetWorldName = newName;
}

