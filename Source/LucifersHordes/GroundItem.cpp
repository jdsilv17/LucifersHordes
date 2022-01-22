// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundItem.h"
#include "Attributes.h"
#include "MeleeWeapon.h"
#include "Ability.h"
#include "Relic.h"
#include "Blueprint/UserWidget.h"
#include "Components/BillboardComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "LucifersHordesCharacter.h"

// Sets default values
AGroundItem::AGroundItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!SphereCollider) {
		SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
		check(SphereCollider != nullptr);

		SphereCollider->InitSphereRadius(1.5f);

		SphereCollider->SetCollisionProfileName(TEXT("OverlapAll"));

		SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AGroundItem::OnOverlapBegin);
		SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AGroundItem::OnOverlapEnd);

		RootComponent = SphereCollider;
	}

	if (!ItemStaticMesh) {
		ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		check(ItemStaticMesh != nullptr);

		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));

		if (Mesh.Succeeded()) {
			ItemStaticMesh->SetStaticMesh(Mesh.Object);
		}
		ItemStaticMesh->SetupAttachment(RootComponent);
	}

	if (!ItemBillboard)
	{
		ItemBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));
		check(ItemBillboard != nullptr);
		static ConstructorHelpers::FObjectFinder<UTexture2D>Sprite(TEXT("Texture2D'/Game/UI/UIAssets/Challenges/BakersDozen.BakersDozen'"));
		if (Sprite.Succeeded())
			ItemBillboard->Sprite = Sprite.Object;
		ItemBillboard->SetupAttachment(RootComponent);
	}

	if (!this->PSC)
	{
		this->PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSC"));

		this->PSC->SetupAttachment(RootComponent);

		if (this->ItemEffect)
			this->PSC->Template = this->ItemEffect;
	}

	if (ItemUITemplate)
	{
		if (!itemUI)
		{
			auto player = GetWorld()->GetFirstPlayerController();
			itemUI = CreateWidget(player, ItemUITemplate);
		}
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> ItemSound(TEXT("SoundCue'/Game/Sound/SFX/PlayerSFX/Bloody_Swing.Bloody_Swing'"));
	if (ItemSound.Succeeded())
	{
		this->ItemSFXCue = ItemSound.Object;

		this->ItemSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("ItemSFX"));

		this->ItemSFX->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AGroundItem::BeginPlay()
{
	Super::BeginPlay();

	OriginalLoc = GetActorLocation();

	OriginalRot = GetActorRotation();


	switch (itemType) {
		case EItemType::None:
			break;
		case EItemType::Relic:
			if (relic)
				SetMyRelic(relic);
			break;
		case EItemType::Weapon:
			if (weapon)
				SetMyWeapon(weapon);
			if (ability)
				SetWepAbility(ability);
			break;
		case EItemType::Ability:
			if (ability)
				SetMyAbility(ability);
			break;
	}

	if (ItemBillboard)
	{
		setBillboard();
	}

	if (ItemSFX && ItemSFXCue)
		ItemSFX->SetSound(ItemSFXCue);
}

// Called every frame
void AGroundItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector targetLoc = GetActorLocation();
	FRotator targetRot = GetActorRotation();

	float RunTime = GetGameTimeSinceCreation();
	float HeightChange = (FMath::Sin(RunTime + DeltaTime) - FMath::Sin(RunTime));
	if (bUp) 
		targetLoc.Z += HeightChange * 20.0f;
	else 
		targetLoc.Z -= HeightChange * 20.0f;

	float DeltaRot = DeltaTime * 20.0f;
	targetRot.Yaw += DeltaRot;

	if (targetLoc.Z > OriginalLoc.Z + Variance && bUp) 
		bUp = false;
	else
		bUp = true;

	SetActorLocationAndRotation(targetLoc, targetRot);
	if (actorRef)
	{
		giveItem();
	}
}

void AGroundItem::SetMyRelic(TSubclassOf<URelic> newRelic)
{
	relic = newRelic;
	bIsWeapon = false;
	//ItemStaticMesh->SetStaticMesh(newRelic.GetDefaultObject()->MyMesh);
	itemType = EItemType::Relic;
	bReadyToEquip = true;
	ItemName = newRelic.GetDefaultObject()->Name;
	ItemDescription = newRelic.GetDefaultObject()->Description;
	Modifiers = newRelic.GetDefaultObject()->Modifiers;
	ModifierValues = newRelic.GetDefaultObject()->Values;
	Icon = newRelic.GetDefaultObject()->Icon;
	setBillboard();
}

void AGroundItem::SetMyWeapon(TSubclassOf<AMeleeWeapon> newWeapon)
{
	weapon = newWeapon;
	bIsWeapon = true;
	//ItemStaticMesh->SetStaticMesh(newWeapon.GetDefaultObject()->GetMesh()->GetStaticMesh());
	itemType = EItemType::Weapon;
	bReadyToEquip = true;
	ItemName = newWeapon.GetDefaultObject()->Name;
	ItemDescription = newWeapon.GetDefaultObject()->Description;
	Modifiers = newWeapon.GetDefaultObject()->Modifiers;
	ModifierValues = newWeapon.GetDefaultObject()->Values;
	Icon = newWeapon.GetDefaultObject()->Icon;
	setBillboard();
}

void AGroundItem::SetWepAbility(TSubclassOf<UAbility> newAbility)
{
	ability = newAbility;
	AbilityName = FText::FromName(ability.GetDefaultObject()->GetName());
	AbilityDesc = ability.GetDefaultObject()->GetEffectDescription();
	AbilityIcon = ability.GetDefaultObject()->GetIcon();
	bAbilityModified = true;

}

void AGroundItem::SetMyAbility(TSubclassOf<UAbility> newAbility)
{
	ability = newAbility;
	itemType = EItemType::Ability;
	ItemName = FText::FromName(ability.GetDefaultObject()->GetName());
	ItemDescription = ability.GetDefaultObject()->GetFluffDescription();
	Icon = ability.GetDefaultObject()->GetIcon();
	setBillboard();
	bReadyToEquip = true;

}

void AGroundItem::OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;
	if (!bReadyToEquip) {
		return;
	}
	if (OtherActor->ActorHasTag(TEXT("Player"))) {
		ALucifersHordesCharacter* chara = Cast<ALucifersHordesCharacter>(OtherActor);
		actorRef = chara;
		chara->setItem(true);
	}
}

void AGroundItem::OnOverlapEnd(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
		return;
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		ALucifersHordesCharacter* chara = Cast<ALucifersHordesCharacter>(OtherActor);
		chara->setItem(false);
		actorRef = nullptr;
		
	}
}

void AGroundItem::giveItem()
{
	if (actorRef)
	{
		ALucifersHordesCharacter* chara = Cast<ALucifersHordesCharacter>(actorRef);
		if (chara->getInteraction())
		{
			switch (itemType)
			{
				case EItemType::None:
					break;
				case EItemType::Weapon:
				{
					auto newWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(weapon);
					newWeapon->SetAbility(ability);
					chara->ChangeWeapon(newWeapon);
					break;
				}
				case EItemType::Relic:
				{
					// might change this to use interface
					chara->GetAttributesComponent()->ApplyEffect(this->relic.GetDefaultObject()->Effect);
					break;
				}
				case EItemType::Ability:
					chara->SetAbility(ability);
					break;
			}
			if (destroyOnPickup)
				Destroy();
			chara->Interacted();
		}
	}
}

void AGroundItem::setBillboard()
{
	if (ItemBillboard)
	{
		ItemBillboard->SetSprite(Icon);
		ItemBillboard->SetHiddenInGame(false, true);
		ItemBillboard->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}