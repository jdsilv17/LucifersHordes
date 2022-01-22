// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMeleeWeapon.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyMeleeWeapon::UEnemyMeleeWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	if (!MyCollider)
	{
		MyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
		MyCollider->BodyInstance.SetCollisionProfileName(TEXT("No Collision"));
		this->MyCollider->OnComponentBeginOverlap.AddDynamic(this, &UEnemyMeleeWeapon::OnOverlapBegin);
		//this->MyCollider->InitializeComponent();
		MyCollider->InitCapsuleSize(25.0f, 50.0f);

		MyCollider->SetupAttachment(this);
	}
}

UCapsuleComponent* UEnemyMeleeWeapon::GetMyCapsuleComponent() const
{
	return this->MyCollider;
}

void UEnemyMeleeWeapon::OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	check(GEngine != nullptr);

	if (OtherActor != nullptr && OtherActor != this->GetOwner() && OtherComp != nullptr)
	{
		if (OtherActor->ActorHasTag(TEXT("Player")) /*&& bIsAttacking*/) // replace with property
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("BONK"));
			UGameplayStatics::ApplyDamage(OtherActor, this->DamageValue, this->GetOwner()->GetInstigatorController(), this->GetOwner(), NULL);
		}
	}
}
