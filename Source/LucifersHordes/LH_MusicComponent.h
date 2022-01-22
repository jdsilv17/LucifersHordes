// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "LH_MusicComponent.generated.h"

class USoundCue;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LUCIFERSHORDES_API ULH_MusicComponent : public UAudioComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
		TArray<USoundCue*> MusicCueArray;

	UFUNCTION(BlueprintCallable)
		void changeVolume();

	UFUNCTION(BlueprintCallable)
		bool playCue(int32 index);

	UFUNCTION(BlueprintCallable)
		void MusicVolume(float newVolume);

	ULH_MusicComponent();


private:
	virtual void BeginPlay() override;

	USoundBase* currentSound;
	int32 soundCount = 0;
	float musicVolume = 1.0f;
};
