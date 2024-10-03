// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameState.h"
#include "Net/UnrealNetwork.h"


void APongGameState::AddScore(int32 PlayerIndex, int32 ScoreToAdd)
{
    if (HasAuthority())
    {
        if (PlayerIndex == 1)
        {
            Player1Score += ScoreToAdd;
        }
        else if (PlayerIndex == 2)
        {
            Player2Score += ScoreToAdd;
        }
    }
}

void APongGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APongGameState, Player1Score);
    DOREPLIFETIME(APongGameState, Player2Score);
}
