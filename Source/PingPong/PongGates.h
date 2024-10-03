// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongGates.generated.h"

class UBoxComponent;

UCLASS()
class PINGPONG_API APongGates : public AActor
{
    GENERATED_BODY()

public:
    APongGates();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_PlayerIndex, Category = "Gate")
    int32 PlayerIndex;

    UFUNCTION(BlueprintImplementableEvent)
    void ChangeColor(int32 Index);

    UFUNCTION()
    void OnRep_PlayerIndex()
    {
        ChangeColor(PlayerIndex);
    }

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBoxComponent* CollisionBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class USceneComponent* Root;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
