// Copyright Epic Games, Inc. All Rights Reserved.

#include "LucifersHordesGameMode.h"
#include "LucifersHordesCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MainMenuHUD.h"

ALucifersHordesGameMode::ALucifersHordesGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter'"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//	//DefaultPawnClass = this->PlayerPawnBPClass->GetClass();
	//}
	
	//HUDClass = AMainMenuHUD::StaticClass();
}
