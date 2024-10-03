// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PongBall.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

UCLASS()
class PINGPONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	void SpawnBall();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	int32 NumPlayers = 0;	

	UPROPERTY(EditAnywhere)
	int32 PlayersToConnect = 2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APongBall> BallClass;

public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
