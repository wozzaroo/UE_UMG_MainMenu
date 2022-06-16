// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WBP/TKWidgetsBase.h"
#include "Styling/SlateColor.h"
#include "TKMainMenu.generated.h"

class UImage;
class UTexture2D;
class UTextBlock;

UCLASS()
class TITANKILL_API UTKMainMenu : public UTKWidgetsBase
{
	GENERATED_BODY()

public:

	UTKMainMenu();

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Bind the background image
	UPROPERTY()
	UTexture2D* textureBG;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* imgBG;

	UPROPERTY()
	UTexture2D* textureBorderContinue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* imgBrdrContinue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* imgBrdrMissions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* imgBrdrNewGame;

	TArray<UImage*> imgCampaignBorders;

	// TextBlocks
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* txtCampaign;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* txtContinue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* txtMission;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* txtNewGame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* txtMultiPlayer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* txtSettings;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* txtQuit;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* txtSelect;

	TArray<UTextBlock*> txtsMainMenu;

	TArray<UTextBlock*> txtsCampaign;

	// Indexes for switching widget 
	int32 CurrentMenuIndex;
    
    int32 CurrentCampaignIndex;

	// Slate colors for highlighted and non highlighted widgets
	FSlateColor TextActiveColor;
	FSlateColor TextInActiveColor;

	FSlateColor CampaignBordersActiveColor;
	FSlateColor CampaignBordersInActiveColor;

	void ScrollDownMenu();

	void ScrollUpMenu();

	void ScrollRightCampaign();

	void ScrollLeftCampaign();

};

