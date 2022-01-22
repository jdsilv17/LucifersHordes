// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		mainMenu = SNew(SMainMenuWidget).mainHud(this);
		//GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(mainMenuContainer, SWeakWidget).PossiblyNullContent(mainMenu.ToSharedRef()));
	}
}
