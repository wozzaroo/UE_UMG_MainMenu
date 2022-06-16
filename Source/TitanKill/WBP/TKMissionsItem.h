// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WBP/TKWidgetsBase.h"
#include "Components/TextBlock.h"
#include "TKMissionsItem.generated.h"

class UImage;
//class UTextBlock;

UCLASS()
class TITANKILL_API UTKMissionsItem : public UTKWidgetsBase
{
	GENERATED_BODY()

	UTKMissionsItem();

public:

	//Bind widget components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ImgMission;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TxtMissionName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TxtMissionDate;	
};
