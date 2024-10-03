// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	int32 NumPlayers = 0;	

	UPROPERTY(EditAnywhere)
	int32 PlayersToConnect = 2;

public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
