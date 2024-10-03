// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameModeBase.h"
#include "PongPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include <Kismet/GameplayStatics.h>

void APongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    NumPlayers++;

    if (NumPlayers >= PlayersToConnect)
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

AActor* APongGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);

    for (AActor* PlayerStartActor : PlayerStarts)
    {
        APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStartActor);
        if (PlayerStart)
        {
            if (!PlayerStart->Tags.Contains(FName("IsTaken")))
            {
                PlayerStart->Tags.Add(FName("IsTaken"));
                return PlayerStart;
            }
        }
    }

    return Super::ChoosePlayerStart_Implementation(Player);
}
