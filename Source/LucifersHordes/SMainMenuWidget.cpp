// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "MainMenuHUD.h"
#include "GameFrameWork/PlayerController.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	mainHud = InArgs._mainHud;

	FMargin tPadding = FMargin(200.0f, 200.0f);
	FMargin bPadding = FMargin(10.0f);

	FText gameTitle = LOCTEXT("Title", "Lucifer's\nHordes");
	FText playButton = LOCTEXT("PlayButton", "Start Game");
	FText challengeButton = LOCTEXT("challengeButton", "Challenges");
	FText optionButton = LOCTEXT("optionButton", "Options");
	FText quitButton = LOCTEXT("quitButton", "Quit");

	FSlateFontInfo gameTitleText = FCoreStyle::Get().GetFontStyle("EmbossedText");
	FSlateFontInfo buttonText = gameTitleText;
	gameTitleText.Size = 60.0f;
	buttonText.Size = 40.0f;

	ChildSlot
	[
		SNew(SOverlay)

		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]

		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(tPadding)
		[
			SNew(SVerticalBox)

			//Title of the game
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(gameTitleText)
				.Text(gameTitle)
				.Justification(ETextJustify::Center)
			]

			//Play Button
			+ SVerticalBox::Slot()
			.Padding(bPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SMainMenuWidget::onPlayClicked)
				[
					SNew(STextBlock)
					.Font(buttonText)
					.Text(playButton)
					.Justification(ETextJustify::Center)
				]
			]

			//Challenges Button
			+ SVerticalBox::Slot()
			.Padding(bPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SMainMenuWidget::onChallengesClicked)
				[
					SNew(STextBlock)
					.Font(buttonText)
					.Text(challengeButton)
					.Justification(ETextJustify::Center)
				]
			]

			//Options Button
			+ SVerticalBox::Slot()
			.Padding(bPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SMainMenuWidget::onOptionsClicked)
				[
					SNew(STextBlock)
					.Font(buttonText)
					.Text(optionButton)
					.Justification(ETextJustify::Center)
				]
			]

			//Quit Button
			+ SVerticalBox::Slot()
			.Padding(bPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SMainMenuWidget::onQuitClicked)
				[
					SNew(STextBlock)
					.Font(buttonText)
					.Text(quitButton)
					.Justification(ETextJustify::Center)
				]
			]
		]
	];
}

FReply SMainMenuWidget::onPlayClicked() const
{
	return FReply::Handled();
}

FReply SMainMenuWidget::onChallengesClicked() const
{
	return FReply::Handled();
}

FReply SMainMenuWidget::onOptionsClicked() const
{
	return FReply::Handled();
}

FReply SMainMenuWidget::onQuitClicked() const
{
	if (mainHud.IsValid())
	{
		if (APlayerController* PC = mainHud->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}

	return FReply::Handled();
}
