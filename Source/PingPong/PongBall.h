// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

UCLASS()
class PINGPONG_API APongBall : public AActor
{
	GENERATED_BODY()

public:
    APongBall();


protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    virtual void Tick(float DeltaTime) override;

    void StartGame();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    class UStaticMeshComponent* BallMesh;

private:
    UPROPERTY(EditAnywhere, Category = "Movement")
    FVector InitialLocation;
};
