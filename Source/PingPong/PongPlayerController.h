// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGameUI();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeScoreUI(int32 Player1Score, int32 Player2Score);
};
