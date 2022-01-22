// Fill out your copyright notice in the Description page of Project Settings.


#include "LH_MusicComponent.h"

ULH_MusicComponent::ULH_MusicComponent()
{
	soundCount = MusicCueArray.Num();
	this->SetIsVirtualized(true);
	this->SetUISound(true);
}

void ULH_MusicComponent::BeginPlay()
{
	if (currentSound)
		this->Play();

}

void ULH_MusicComponent::changeVolume()
{
	this->AdjustVolume(0.0f, musicVolume, EAudioFaderCurve::Linear);
}

void ULH_MusicComponent::MusicVolume(float newVolume)
{
		this->musicVolume = newVolume;
}

bool ULH_MusicComponent::playCue(int index)
{
	bool ableToPlay = false;
	if (index >= 0 && index < soundCount)
		currentSound = (USoundBase*)MusicCueArray[index];
	if (currentSound)
	{
		this->SetSound(currentSound);
		ableToPlay = true;
	}
	this->Play();
	return ableToPlay;
}

