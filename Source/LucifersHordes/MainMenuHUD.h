// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	TSharedPtr<class SMainMenuWidget> mainMenu;
	TSharedPtr<class SWidget> mainMenuContainer;

	virtual void BeginPlay() override;
};
