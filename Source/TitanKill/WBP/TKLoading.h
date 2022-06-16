// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WBP/TKWidgetsBase.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "TKLoading.generated.h"

//Forward declarations
class UImage;
class UTexture2D;

UCLASS()
class TITANKILL_API UTKLoading : public UTKWidgetsBase
{
	GENERATED_BODY()
	
public:

	UTKLoading();

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Bind the images
	UPROPERTY()
	UTexture2D* textureBG;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* imgBG;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* imgLoadingMovie;

	//Bind the widget animation
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* animLoading;

	//Delegates for when the loading animation starts and finishes
	FWidgetAnimationDynamicEvent AnimLoadingStartedDelegate;
	FWidgetAnimationDynamicEvent AnimLoadingEndedDelegate;

	UFUNCTION()
	void AnimationStarted();

	UFUNCTION()
	void AnimationEnded();

    UFUNCTION()
    void LoadLevel();

	// Get the widget animation by name
	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	// Play the widget anumation
	bool PlayAnimationByName(FName AnimationName,
		float StartAtTime,
		int32 NumLoopsToPlay,
		EUMGSequencePlayMode::Type PlayMode,
		float PlaybackSpeed);

protected:
	// Map of widget animations
	TMap<FName, UWidgetAnimation*> AnimationsMap;

	// Add the widget animations
	void FillAnimationsMap();
};