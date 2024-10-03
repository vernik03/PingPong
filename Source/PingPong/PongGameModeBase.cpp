// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameModeBase.h"
#include "PongPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include <Kismet/GameplayStatics.h>
#include "PongBall.h"
#include "PongGates.h"

void APongGameModeBase::SpawnBall()
{
	if (BallClass)
	{
        APongBall* Ball = GetWorld()->SpawnActor<APongBall>(BallClass, FVector::ZeroVector, FRotator::ZeroRotator);
        if (Ball)
        {
            Ball->StartGame();
        }
	}
}

void APongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    NumPlayers++;

    if (NumPlayers >= PlayersToConnect)
    {
        TArray<AActor*> GateActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APongGates::StaticClass(), GateActors);

		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APongPlayerController* Controller = Cast<APongPlayerController>(Iterator->Get());
			if (Controller != nullptr)
			{
                Controller->PlayerIndex = NumPlayers;
                if (FVector::Distance(GateActors[0]->GetActorLocation(), Controller->GetPawn()->GetActorLocation()) < FVector::Distance(GateActors[1]->GetActorLocation(), Controller->GetPawn()->GetActorLocation()))
                {
					Controller->PlayerIndex = 1;
                    Cast<APongGates>(GateActors[0])->PlayerIndex = 1;
				}
				else
				{
					Controller->PlayerIndex = 2;
                    Cast<APongGates>(GateActors[1])->PlayerIndex = 2;
                }
				Controller->StartGame();
                NumPlayers--;
			}
		}
        SpawnBall();
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
