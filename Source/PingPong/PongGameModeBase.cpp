// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameModeBase.h"
#include "PongPlayerController.h"

void APongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    NumPlayers++;

    if (NumPlayers >= 2)
    {
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APongPlayerController* Controller = Cast<APongPlayerController>(Iterator->Get());
			if (Controller != nullptr)
			{
				Controller->StartGame();
			}
		}
    }
}
