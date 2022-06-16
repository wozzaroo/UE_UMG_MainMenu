// Fill out your copyright notice in the Description page of Project Settings.


#include "TKLoading.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"

UTKLoading::UTKLoading()
{
	// Load the assets
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureBG(TEXT("/Game/Textures/textureBG"));
	
	// If successfull, assign to variables
	if(TextureBG.Succeeded())
	{
		textureBG = TextureBG.Object;
	}
}

void UTKLoading::NativeConstruct()
{
	// Fill the widget animations map
	FillAnimationsMap();

	imgBG->SetBrushFromTexture(textureBG);

	AnimLoadingStartedDelegate.BindDynamic(this, &UTKLoading::AnimationStarted);
	AnimLoadingEndedDelegate.BindDynamic(this, &UTKLoading::AnimationEnded);

	BindToAnimationStarted(animLoading, AnimLoadingStartedDelegate);
	BindToAnimationFinished(animLoading, AnimLoadingEndedDelegate);

	Super::NativeConstruct();
}

// Animations map
void UTKLoading::FillAnimationsMap()
{
	AnimationsMap.Empty();
	
	UProperty* Prop = GetClass()->PropertyLink;

	// Run through all properties of this class to find any widget animations
	while (Prop != nullptr)
	{
		// Only interested in object properties
		if (Prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);

			// Only want the properties that are widget animations
			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);

				UWidgetAnimation* WidgetAnim = Cast<UWidgetAnimation>(Obj);

				if (WidgetAnim != nullptr && WidgetAnim->MovieScene != nullptr)
				{
					FName AnimName = WidgetAnim->MovieScene->GetFName();
					AnimationsMap.Add(AnimName, WidgetAnim);
				}
			}
		}

		Prop = Prop->PropertyLinkNext;
	}
}

// Get the animation to play
UWidgetAnimation* UTKLoading::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnim = AnimationsMap.Find(AnimationName);
	if (WidgetAnim)
	{
		return *WidgetAnim;
	}
	return nullptr;
}

// Play the animation
bool UTKLoading::PlayAnimationByName(FName AnimationName,
	float StartAtTime,
	int32 NumLoopsToPlay,
	EUMGSequencePlayMode::Type PlayMode,
	float PlaybackSpeed)
{
	UWidgetAnimation* WidgetAnim = GetAnimationByName(AnimationName);
	if (WidgetAnim)
	{
		PlayAnimation(WidgetAnim, StartAtTime, NumLoopsToPlay, PlayMode, PlaybackSpeed);
		return true;
	}
	return false;
}

void UTKLoading::AnimationStarted()
{

}

void UTKLoading::AnimationEnded()
{
	LoadLevel();
}


void UTKLoading::LoadLevel()
{
	UGameplayStatics::OpenLevel(this, FName("lvlPiercer"), true);
}
   
