// Fill out your copyright notice in the Description page of Project Settings.

#include "EnvironmentalEffects.h"

AEnvironmentalEffects::AEnvironmentalEffects()
{
	OnActorBeginOverlap.AddDynamic(this, &AEnvironmentalEffects::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AEnvironmentalEffects::OnOverlapEnd);

	thistleDT.Add(EDamageTypes::None);
}

AEnvironmentalEffects::AEnvironmentalEffects(EVHType hazard, int effectMod)
{
	Hazard = hazard;
	Effect *= effectMod;
}

void AEnvironmentalEffects::BeginPlay()
{
	Super::BeginPlay();
	
	Effect *= EffectModifier;
}

void AEnvironmentalEffects::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	switch (Hazard)
	{
	case EVHType::BottomlessPit:
		if (OtherActor && (OtherActor != this) && (OtherActor->ActorHasTag(TEXT("Enemy")) || OtherActor->ActorHasTag(TEXT("Player"))))
		{
			FVector currLocation = OtherActor->GetActorLocation();
			FVector transportVector = AEnvironmentalEffects::RandomXYVector(-500.0f, 500.0f);
			transportVector.Z = 5000.0f;
			OtherActor->SetActorLocation(currLocation + transportVector, false, nullptr, ETeleportType::TeleportPhysics);
		}
		break;
	case EVHType::WindFunnel:
		break;
	case EVHType::Thistle:
		if (OtherActor && (OtherActor != this) && (OtherActor->ActorHasTag(TEXT("Player")) || (OtherActor->ActorHasTag(TEXT("Enemy")))))
		{
			auto LHC = Cast<ABaseCharacter>(OtherActor);
			
			ULH_GameplayStatics::ApplyDamage_(LHC, Effect, this->GetInstigatorController(), this, NULL, thistleDT);
		}
		break;
	case EVHType::IceFloor:
		break;
	case EVHType::TarPool:
		break;
	case EVHType::LavaFloor:
		break;
	case EVHType::ToxicPool:
		break;
	default:
		break;
	}
}

void AEnvironmentalEffects::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	
}

FVector AEnvironmentalEffects::RandomXYVector(float min, float max)
{
	float x = FMath::FRandRange(min, max);
	float y = FMath::FRandRange(min, max);
	return FVector(x, y, 0.0f);
}