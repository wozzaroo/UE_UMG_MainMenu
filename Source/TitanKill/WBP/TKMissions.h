// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WBP/TKWidgetsBase.h"
#include "Engine/DataTable.h"
#include "TKMissions.generated.h"

// Forward declarations
class UScrollBox;
class UTKMissionsItem;
class UTexture2D;
class UImage;


USTRUCT(BlueprintType)
struct FMissionsData : public FTableRowBase
{
	GENERATED_BODY()

	//Bind widget components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* MissionTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText MissionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	FText MissionsCompletedData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	FText MissionsBonus;
};

UCLASS()
class TITANKILL_API UTKMissions : public UTKWidgetsBase
{
	GENERATED_BODY()
	
public:

	UTKMissions();

	virtual void NativeConstruct() override;

	UPROPERTY()
	UTexture2D* textureBG;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* imgBG;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* MissionsScrollBox;

    UPROPERTY()
    UTKMissionsItem* MissionsItemWidget;

    // UMG WBP classes and pointers
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Demo")
    TSubclassOf<UTKMissionsItem> MissionsItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mission Data")
	UDataTable* MissionsDataTable;

	UPROPERTY()
	FMissionsData MissionsData;

};
