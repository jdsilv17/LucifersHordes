// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"


/**
 * 
 */
class SMainMenuWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMainMenuWidget) {}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, mainHud)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply onPlayClicked() const;
	FReply onChallengesClicked() const;
	FReply onOptionsClicked() const;
	FReply onQuitClicked() const;

	TWeakObjectPtr<class AMainMenuHUD> mainHud;

	virtual bool SupportsKeyboardFocus() const override 
	{ 
		return true; 
	};
};
