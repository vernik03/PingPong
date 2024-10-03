// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreDelegate);

UCLASS()
class PINGPONG_API APongGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    UPROPERTY(ReplicatedUsing = OnRep_PlayerScore, VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 Player1Score = 0;

    UPROPERTY(ReplicatedUsing = OnRep_PlayerScore, VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 Player2Score = 0;

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 PlayerIndex, int32 ScoreToAdd);

    UPROPERTY(BlueprintAssignable, Category = "Score")
    FScoreDelegate OnScoreDelegate;

    UFUNCTION()
    void OnRep_PlayerScore()
    {
        OnScoreDelegate.Broadcast();
    }

    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};
