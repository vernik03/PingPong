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
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable)
	void StartGame();

	UFUNCTION(Client, Reliable)
	void ChangeScore();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGameUI();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeScoreUI(int32 Player1Score, int32 Player2Score);

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 PlayerIndex;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
