// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Fighter2DGameMode.generated.h"

/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of Fighter2DCharacter
 */
UCLASS(minimalapi)
class AFighter2DGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFighter2DGameMode();

    /** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
    /** Called when the game starts. */
    virtual void BeginPlay() override;

    /** The widget class we will use as our menu when the game starts. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> StartingWidgetClass;

    /** The widget instance that we are using as our menu. */
    UPROPERTY()
        UUserWidget* CurrentWidget;
};
