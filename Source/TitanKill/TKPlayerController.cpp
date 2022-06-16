// Fill out your copyright notice in the Description page of Project Settings.


#include "TKPlayerController.h"
#include "WBP/TKMainMenu.h"
#include "WBP/TKLoading.h"
#include "WBP/TKMissions.h"
#include "TitanKillCharacter.h"

// Load the WBP, asssign the classes
ATKPlayerController::ATKPlayerController()
     :
     APlayerController()
 {

    //Load the WBP's
  	static ConstructorHelpers::FClassFinder<UTKMainMenu> WBP_MainMenu(TEXT("/Game/WBP/WBP_MainMenu.WBP_MainMenu_C"));
  	static ConstructorHelpers::FClassFinder<UTKLoading> WBP_Loading(TEXT("/Game/WBP/WBP_Loading.WBP_Loading_C"));
  	static ConstructorHelpers::FClassFinder<UTKMissions> WBP_Missions(TEXT("/Game/WBP/WBP_Missions.WBP_Missions_C"));

    // Check if loaded successfully
	if (WBP_MainMenu.Class != NULL)
	{
		MainMenuClass = WBP_MainMenu.Class;
	}

   if (WBP_Loading.Class != NULL)
	{
		LoadingClass = WBP_Loading.Class;
	}

   if (WBP_Missions.Class != NULL)
	{
		MissionsClass = WBP_Missions.Class;
	}
 }


void ATKPlayerController::BeginPlay()
{
   Super::BeginPlay();

   Player = Cast<ATitanKillCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

   // Get the level name and remove the default editor prefixes.
   UWorld* TheWorld = GetWorld();

   FString CurrentLevel = TheWorld->GetMapName();
   CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

   // Open the corresponding level based on the level name and add the WBP for this level.
   if (CurrentLevel == "lvlMainMenu")
   {
      if (MainMenuClass != nullptr)
      {
         MainMenuWidget = CreateWidget<UTKMainMenu>(GetWorld(), MainMenuClass);
         if (MainMenuWidget != nullptr)
         {
            MainMenuWidget->AddToViewport();
         }
      }   
   }
 }

// Bind our Inputs for the Game controller
void ATKPlayerController::SetupInputComponent()
 {
   Super::SetupInputComponent();
   //InputComponent->BindKey(EKeys::GetAllKeys, IE_Released, this, &ATKPlayerController::AFunction);
   InputComponent->BindAction("DetectKey", IE_Pressed, this, &ATKPlayerController::GetGamePadKey);

 }

// Get the Gamepad keys
// Not the best way to do it for sure
// Scrolling functionality
void ATKPlayerController::GetGamePadKey(FKey key)
{
  
   FText KeyName = key.GetDisplayName();
 
   if(KeyName.ToString() == "Gamepad D-pad Up")
   { 
      MainMenuWidget->ScrollUpMenu();
   }

   if(KeyName.ToString() == "Gamepad D-pad Down")
   {
      MainMenuWidget->ScrollDownMenu();
   }

   if(KeyName.ToString() == "Gamepad D-pad Right")
   {  
      MainMenuWidget->ScrollRightCampaign();
   }

   if(KeyName.ToString() == "Gamepad D-pad Left")
   {  
      MainMenuWidget->ScrollLeftCampaign();
   }

   // Create the corresponding widget based on the level name
   if(KeyName.ToString() == "Gamepad Face Button Bottom")
   {  
      // Get the level name and remove the default editor prefixes.
      UWorld* TheWorld = GetWorld();

      FString CurrentLevel = TheWorld->GetMapName();
      CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

      if (CurrentLevel == "lvlMainMenu")
      {
         if(MainMenuWidget->CurrentMenuIndex == 0 && MainMenuWidget->CurrentCampaignIndex == 0)
         {
            if (LoadingClass != nullptr)
            {
               if(!animLoadingStarted)
               {
               
                  UE_LOG(LogTemp, Warning, TEXT("PlayAnimationByName:"));

                  MainMenuWidget->RemoveFromParent();
                  LoadingWidget = CreateWidget<UTKLoading>(GetWorld(), LoadingClass);
                  if (LoadingWidget != nullptr)
                  {
                     LoadingWidget->AddToViewport();
                     LoadingWidget->PlayAnimationByName("animLoading", 0.0f, 5, EUMGSequencePlayMode::Forward, 1.0f);
                     animLoadingStarted = true;
                  }
               }
            } 
         }   
         if(MainMenuWidget->CurrentMenuIndex == 0 && MainMenuWidget->CurrentCampaignIndex == 1)
         {
            if (MissionsClass != nullptr)
            {
               MainMenuWidget->RemoveFromParent();
               MissionsWidget = CreateWidget<UTKMissions>(GetWorld(), MissionsClass);
               MissionsWidget->AddToViewport(); 
            } 
         }   
      }
      else
      {
         Player->Jump();
      }
      UE_LOG(LogTemp, Warning, TEXT("Select Pressed:"));
   
   }
}