// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_AnimNotifyState.h"
#include "BaseCharacter.h"

void UAbility_AnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{

}

void UAbility_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (character)
	{
		character->bIsInvincible = true;
	}
}

void UAbility_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (character)
	{
		character->bIsInvincible = false;
	}
}
