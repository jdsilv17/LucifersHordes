// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEncounter.h"
#include "Door.h"

void ABossEncounter::FinishedEncounter()
{
	ARoomEncounter::FinishedEncounter();

	check(GEngine != nullptr)
		if (Door) {
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = GetInstigator();
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			ADoor* newDoor = GetWorld()->SpawnActor<ADoor>(Door, GetActorLocation(), GetActorRotation(), spawnParams);

			if (NextLevel.IsNone())
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Set NextLevel"));
			newDoor->SetTargetWorld(NextLevel);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Set Door in BP"));
		}
}
int ABossEncounter::Died_Implementation()
{
	TotalDead++;
	if (TotalDead == Target) {
		FinishedEncounter();
	}
	return 0;
}