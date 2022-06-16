// Fill out your copyright notice in the Description page of Project Settings.


#include "TKMainMenu.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UTKMainMenu::UTKMainMenu()
{
	// Load the assets
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureBG(TEXT("/Game/Textures/textureBG"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureBorderContinue(TEXT("/Game/Textures/brdrContinue"));

	// If successfull, assign to variables

	if(TextureBG.Succeeded())
	{
		textureBG = TextureBG.Object;
	}

	if(TextureBorderContinue.Succeeded())
	{
		textureBorderContinue = TextureBorderContinue.Object;
	}
}

// Set the lements of the UMG, set the colors of active and inactive elements
void UTKMainMenu::NativeConstruct()
{
	imgBG->SetBrushFromTexture(textureBG);
	imgBrdrContinue->SetBrushFromTexture(textureBorderContinue);
	imgBrdrMissions->SetBrushFromTexture(textureBorderContinue);
	imgBrdrNewGame->SetBrushFromTexture(textureBorderContinue);

	txtsMainMenu.Add(txtCampaign);
	txtsMainMenu.Add(txtMultiPlayer);
	txtsMainMenu.Add(txtSettings);
	txtsMainMenu.Add(txtQuit);

	txtsCampaign.Add(txtContinue);	
	txtsCampaign.Add(txtMission);
	txtsCampaign.Add(txtNewGame);

	imgCampaignBorders.Add(imgBrdrContinue);
	imgCampaignBorders.Add(imgBrdrMissions);
	imgCampaignBorders.Add(imgBrdrNewGame);

 	TextActiveColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	TextInActiveColor = FLinearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
	CampaignBordersActiveColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	CampaignBordersInActiveColor = FLinearColor(0.25f, 0.25f, 0.25f, 1.0f);

	for(int i = 0; i < txtsMainMenu.Num(); i++)
	{
		txtsMainMenu[i]->SetColorAndOpacity(TextInActiveColor);
	}

	for(int i = 0; i < txtsCampaign.Num(); i++)
	{
		txtsCampaign[i]->SetColorAndOpacity(TextInActiveColor);
	}

	txtsMainMenu[0]->SetColorAndOpacity(TextActiveColor);
	txtsCampaign[0]->SetColorAndOpacity(TextActiveColor);
	
	imgCampaignBorders[1]->SetBrushTintColor(CampaignBordersInActiveColor);
	imgCampaignBorders[2]->SetBrushTintColor(CampaignBordersInActiveColor);

	CurrentMenuIndex = 0;
    CurrentCampaignIndex = 0;

	Super::NativeConstruct();
}

//Scrolling through the widgets bases on the current index
void UTKMainMenu::ScrollDownMenu()
{
	CurrentMenuIndex++;

	if(CurrentMenuIndex == 4)
	{
		CurrentMenuIndex = 0;
		txtsMainMenu[txtsMainMenu.Num() -1]->SetColorAndOpacity(TextInActiveColor);
		txtsMainMenu[CurrentMenuIndex]->SetColorAndOpacity(TextActiveColor);
		txtsCampaign[CurrentMenuIndex]->SetColorAndOpacity(TextActiveColor);
		imgCampaignBorders[CurrentMenuIndex]->SetBrushTintColor(CampaignBordersActiveColor);
	}
	else
	{
		for(int i = 0; i < txtsCampaign.Num(); i++)
		{
			txtsCampaign[i]->SetColorAndOpacity(TextInActiveColor);
			imgCampaignBorders[i]->SetBrushTintColor(CampaignBordersInActiveColor);
		}

		CurrentCampaignIndex = 0;
		txtsMainMenu[CurrentMenuIndex - 1]->SetColorAndOpacity(TextInActiveColor);
 		txtsMainMenu[CurrentMenuIndex]->SetColorAndOpacity(TextActiveColor);
	}
}

void UTKMainMenu::ScrollUpMenu()
{
	CurrentMenuIndex--;

	if(CurrentMenuIndex == -1)
	{
		CurrentMenuIndex = 3;
		txtsMainMenu[0]->SetColorAndOpacity(TextInActiveColor);
		txtsMainMenu[txtsMainMenu.Num() -1]->SetColorAndOpacity(TextActiveColor);
		
		CurrentCampaignIndex = 0;
		for(int i = 0; i < txtsCampaign.Num(); i++)
		{
			txtsCampaign[i]->SetColorAndOpacity(TextInActiveColor);
			imgCampaignBorders[i]->SetBrushTintColor(CampaignBordersInActiveColor);
		}
	}
	else
	{
		txtsMainMenu[CurrentMenuIndex]->SetColorAndOpacity(TextActiveColor);
		txtsMainMenu[CurrentMenuIndex + 1]->SetColorAndOpacity(TextInActiveColor);
		
		if(CurrentMenuIndex == 0)
		{
			txtsCampaign[CurrentMenuIndex]->SetColorAndOpacity(TextActiveColor);
			imgCampaignBorders[CurrentMenuIndex]->SetBrushTintColor(CampaignBordersActiveColor);
		}
	}
}

void UTKMainMenu::ScrollRightCampaign()
{
	if(CurrentMenuIndex == 0)
	{
		CurrentCampaignIndex++;

		if(CurrentCampaignIndex == 3)
		{
			CurrentCampaignIndex = 0;
			txtsCampaign[CurrentCampaignIndex]->SetColorAndOpacity(TextActiveColor);
			txtsCampaign[txtsCampaign.Num() - 1]->SetColorAndOpacity(TextInActiveColor);
			imgCampaignBorders[CurrentCampaignIndex]->SetBrushTintColor(CampaignBordersActiveColor);
			imgCampaignBorders[imgCampaignBorders.Num() - 1]->SetBrushTintColor(CampaignBordersInActiveColor);
		}
		else
		{
			txtsCampaign[CurrentCampaignIndex - 1]->SetColorAndOpacity(TextInActiveColor);
			txtsCampaign[CurrentCampaignIndex]->SetColorAndOpacity(TextActiveColor);
			imgCampaignBorders[CurrentCampaignIndex - 1]->SetBrushTintColor(CampaignBordersInActiveColor);
			imgCampaignBorders[CurrentCampaignIndex]->SetBrushTintColor(CampaignBordersActiveColor);
		}
	}
}

void UTKMainMenu::ScrollLeftCampaign()
{
	if(CurrentMenuIndex == 0)
	{
		CurrentCampaignIndex--;

		if(CurrentCampaignIndex == -1)
		{
			CurrentCampaignIndex = 2;
			txtsCampaign[CurrentCampaignIndex]->SetColorAndOpacity(TextActiveColor);
			txtsCampaign[0]->SetColorAndOpacity(TextInActiveColor);
			imgCampaignBorders[CurrentCampaignIndex]->SetBrushTintColor(CampaignBordersActiveColor);
			imgCampaignBorders[0]->SetBrushTintColor(CampaignBordersInActiveColor);
		}
		else
		{
			txtsCampaign[CurrentCampaignIndex + 1]->SetColorAndOpacity(TextInActiveColor);
			txtsCampaign[CurrentCampaignIndex]->SetColorAndOpacity(TextActiveColor);
			imgCampaignBorders[CurrentCampaignIndex + 1]->SetBrushTintColor(CampaignBordersInActiveColor);
			imgCampaignBorders[CurrentCampaignIndex]->SetBrushTintColor(CampaignBordersActiveColor);
		}
	}
}
