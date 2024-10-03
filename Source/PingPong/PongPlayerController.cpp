// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayerController.h"

#include <Net/UnrealNetwork.h>

#include "PongGameState.h"

void APongPlayerController::StartGame_Implementation()
{
	StartGameUI();
}

void APongPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetGameState<APongGameState>()->OnScoreDelegate.AddDynamic(this, &APongPlayerController::ChangeScore);
}

void APongPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongPlayerController, PlayerIndex);
}

void APongPlayerController::ChangeScore_Implementation()
{
	APongGameState* GameState = GetWorld()->GetGameState<APongGameState>();
	ChangeScoreUI(GetWorld()->GetGameState<APongGameState>()->Player1Score, GetWorld()->GetGameState<APongGameState>()->Player2Score);
}
