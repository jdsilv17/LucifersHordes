//=====================================================
// Modified By: Kurtis McCammon, Justin DaSilva
// Last Updated: 5/8/2021
//=====================================================


#include "MeleeWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Character.h"

#include "LH_GameplayStatics.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
	if (!dummy) {
		dummy = CreateDefaultSubobject<USceneComponent>(TEXT("KurtisIsADummy"));

		check(dummy != nullptr);

		RootComponent = dummy;
	}

	if (!MyMesh) {

		MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		check(MyMesh != nullptr);

		//static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));

		//if (Mesh.Succeeded()) {
		//	MyMesh->SetStaticMesh(Mesh.Object);
		//}
		MyMesh->SetGenerateOverlapEvents(false);
		MyMesh->SetCollisionProfileName(TEXT("NoCollision"));

		MyMesh->SetupAttachment(RootComponent);
	}

	if (!MyWeaponCollider) {
		MyWeaponCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollider"));
		check(MyWeaponCollider != nullptr);

		MyWeaponCollider->SetGenerateOverlapEvents(true);
		MyWeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		this->MyWeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnOverlapBegin);
		//this->MyWeaponCollider->OnComponentEndOverlap.AddDynamic(this, &AMeleeWeapon::OnOverlapEnd);
		//this->MyWeaponCollider->OnComponentHit.AddDynamic(this, &AMeleeWeapon::OnCompHit);

		MyWeaponCollider->InitCapsuleSize(25.0f, 50.0f);

		MyWeaponCollider->SetupAttachment(MyMesh);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> BloodyBladeCueObj(TEXT("SoundCue'/Game/Sound/SFX/PlayerSFX/Bloody_Swing.Bloody_Swing'"));
	if (BloodyBladeCueObj.Succeeded())
	{
		BloodyBladeCue = BloodyBladeCueObj.Object;

		BloodyBladeAC = CreateDefaultSubobject<UAudioComponent>(TEXT("BloodyBladeAC"));

		BloodyBladeAC->SetupAttachment(RootComponent);
	}

	if (!this->PSC)
	{
		this->PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSC"));

		this->PSC->SetupAttachment(RootComponent);
	}
	//if (!this->HitPSC)
	//{
	//	//this->HitPSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitPSC"));

	//	//this->HitPSC->SetupAttachment(RootComponent);
	//}

	SetCanBeDamaged(false);

	this->Values = FText::FromString(FString::SanitizeFloat(this->DamageValue) + " Damage");
}

UStaticMeshComponent* AMeleeWeapon::GetMesh()
{
	return MyMesh;
}

UAbility* AMeleeWeapon::TryGetAbility() const
{
	UAbility* abilityToGet = this->Ability.GetDefaultObject();

	if (abilityToGet) return abilityToGet;

	return nullptr;
}

void AMeleeWeapon::SetAbility(TSubclassOf<UAbility> newAbility)
{
	this->Ability = newAbility;
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (this->MyWeaponCollider)
	{
		this->SetActorEnableCollision(false);
	}

	if (BloodyBladeAC && BloodyBladeCue)
	{
		BloodyBladeAC->SetSound(BloodyBladeCue);
	}

	//if (this->HitPSC && this->HitEffect)
	//{
	//	this->HitPSC->Template = this->HitEffect;
	//}

	this->Values = FText::FromString(FString::SanitizeFloat(this->DamageValue) + " Damage");
}

void AMeleeWeapon::OnOverlapBegin
(
	UPrimitiveComponent* OverLapComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult	)
{
	check(GEngine != nullptr);

	this->ActorIgnoreList.Add(this->GetAttachParentActor());

	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (OtherActor->IsA<ACharacter>()
			&& OtherActor->Tags != this->GetAttachParentActor()->Tags
			&& OtherActor->CanBeDamaged()
			&& !this->ActorIgnoreList.Contains(OtherActor)
			)
		{
			// Ignore last actor hit to avoid damaging multiple times in a single attack
			this->ActorIgnoreList.Add(OtherActor);

			// Actually apply the damage
			if (auto character = Cast<ABaseCharacter>(OtherActor))
				ULH_GameplayStatics::ApplyDamage_(character, this->DamageValue, this->GetInstigatorController(), this->GetAttachParentActor(), NULL, this->DamageTypes);

			// Spawn Hit particle effect
			if (/*this->HitPSC->Template &&*/ !this->HitLocation.IsNearlyZero())
			{
				this->HitPSC = ULH_GameplayStatics::SpawnEmitterAtLocation(GetWorld(), this->HitEffect, this->HitLocation);
				//this->HitPSC->OnParticleCollide
				this->HitLocation = FVector::ZeroVector;
			}

			if (GetAttachParentActor()->ActorHasTag("Player"))
			{
				// Hit pause
				ULH_GameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.15f);
				GetWorldTimerManager().SetTimer(this->UnusedHandle, this, &AMeleeWeapon::ResetTime, 0.01f, false);

				// Strike Assist: Accessibility setting - exclusive to player
				FVector Dir = GetAttachParentActor()->GetActorRightVector();
				FVector Offset = OtherActor->GetActorLocation() - GetAttachParentActor()->GetActorLocation();
				Offset = Offset.GetSafeNormal();
				float dotToTarget = FVector::DotProduct(Dir, Offset);
				FRotator rotToTarget(0.0f, dotToTarget * 25.0f, 0.0f);
				GetAttachParentActor()->AddActorWorldRotation(rotToTarget.Quaternion());
			}
		
			// Play Hit SFX
			// change this to be more generic
			if (BloodyBladeAC && BloodyBladeCue)
			{
				BloodyBladeAC->Play(0.0f);
			}
		}
	}
}

void AMeleeWeapon::ResetTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void AMeleeWeapon::ApplyEffectToAttribute(FLH_GameplayEffect EffectToApply)
{
}

void AMeleeWeapon::AddTempDamageType(EDamageTypes DamageType)
{
	// if adding none remove previous
	if (this->DamageTypes.Num() != 0)
	{
		if (DamageType == EDamageTypes::None)
		{
			this->DamageTypes.Pop();
			return;
		}
		else if (DamageType == EDamageTypes::LifeStealFrom)
		{
			if (this->DamageTypes.Contains(EDamageTypes::LifeStealFrom))
				return;
		}
		this->DamageTypes.Add(DamageType);
	}
	else if (DamageType != EDamageTypes::None)
		this->DamageTypes.Add(DamageType);
}

