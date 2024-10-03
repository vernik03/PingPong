// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGates.h"
#include "Components/BoxComponent.h"
#include "PongBall.h"
#include "PongGameState.h"
#include "Kismet/GameplayStatics.h"
#include <Net/UnrealNetwork.h>

APongGates::APongGates()
{
    PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = Root;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(Root);

    CollisionBox->SetGenerateOverlapEvents(true);

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APongGates::OnOverlapBegin);
}

void APongGates::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APongGates, PlayerIndex);
}

void APongGates::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    APongBall* PongBall = Cast<APongBall>(OtherActor);
    if (PongBall && HasAuthority())
    {
        APongGameState* GameState = GetWorld()->GetGameState<APongGameState>();
        if (GameState)
        {
            GameState->AddScore(PlayerIndex, 1);
        }

        PongBall->StartGame();

    }
}
