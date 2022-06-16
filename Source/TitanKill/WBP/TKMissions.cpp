// Fill out your copyright notice in the Description page of Project Settings.


#include "TKMissions.h"
#include "TKMissionsItem.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"

UTKMissions::UTKMissions()
{
	// Load the assets
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureBG(TEXT("/Game/Textures/textureBG"));
	static ConstructorHelpers::FClassFinder<UTKMissionsItem> WBP_MissionsItem(TEXT("/Game/WBP/WBP_MissionsItem.WBP_MissionsItem_C"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MissionsDataTableObject(TEXT("/Game/DataTables/DT_MissionsData"));

	// If successfull, assign to variables
	if(TextureBG.Succeeded())
	{
		textureBG = TextureBG.Object;
	}

    if (WBP_MissionsItem.Class != NULL)
	{
		MissionsItemClass = WBP_MissionsItem.Class;
	}

    //Get the DataTable object
    if(MissionsDataTableObject.Succeeded())
    {
        MissionsDataTable = MissionsDataTableObject.Object;
    }
}


// Setup the missions list from Datatable
void UTKMissions::NativeConstruct()
{

	imgBG->SetBrushFromTexture(textureBG);

    FString ContextString;
    TArray<FName> RowNames =  MissionsDataTable->GetRowNames();

    for(int i = 0; i < RowNames.Num(); i++)
    {
        MissionsItemWidget = CreateWidget<UTKMissionsItem>(GetWorld(), MissionsItemClass);

        MissionsScrollBox->AddChild(MissionsItemWidget);

        FMissionsData* aa = MissionsDataTable->FindRow<FMissionsData>(RowNames[i], ContextString);
        
        MissionsItemWidget->TxtMissionName->SetText(FText::FromName(RowNames[i]));
        MissionsItemWidget->TxtMissionDate->SetText(aa->MissionsCompletedData);
        MissionsItemWidget->TxtMissionName->SetText(aa->MissionsBonus);
        MissionsItemWidget->ImgMission->SetBrushFromTexture(aa->MissionTexture);
    }
    

    Super::NativeConstruct();
}

