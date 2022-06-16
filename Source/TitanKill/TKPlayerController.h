// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TKPlayerController.generated.h"

// Forward declarations
class UTKMainMenu;
class UTKLoading;
class UTKMissions;
class ATitanKillCharacter;

UCLASS()
class TITANKILL_API ATKPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATKPlayerController();

    //Character refernce
    ATitanKillCharacter* Player;

	// Override Input Component
 	virtual void SetupInputComponent() override;

	// UMG WBP classes and pointers
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Demo")
    TSubclassOf<UTKMainMenu> MainMenuClass;

    UPROPERTY()
    UTKMainMenu* MainMenuWidget;

    // UMG WBP classes and pointers
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Demo")
    TSubclassOf<UTKLoading> LoadingClass;

    UPROPERTY()
    UTKLoading* LoadingWidget;

    // UMG WBP classes and pointers
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Demo")
    TSubclassOf<UTKMissions> MissionsClass;

    UPROPERTY()
    UTKMissions* MissionsWidget;

    //Get Gamepad keys
    void GetGamePadKey(FKey key);
    
    // Has the loading animation started
	bool animLoadingStarted;

protected:

    virtual void BeginPlay() override;

};



