// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"


APongBall::APongBall()
{
    PrimaryActorTick.bCanEverTick = true;
    SetReplicates(true);
    SetReplicateMovement(true);

    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;

    BallMesh->OnComponentHit.AddDynamic(this, &APongBall::OnHit);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = BallMesh;
    ProjectileMovement->bShouldBounce = true;
    ProjectileMovement->Bounciness = 1.0f; 
    ProjectileMovement->Friction = 0.0f;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
    ProjectileMovement->BounceVelocityStopSimulatingThreshold = 0.0f;
}

void APongBall::BeginPlay()
{
    Super::BeginPlay();

    ProjectileMovement->Velocity = FVector::ZeroVector;
}

void APongBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (!HasAuthority())
    {
        return;
    }

    FVector CurrentVelocity = ProjectileMovement->Velocity;

    if (CurrentVelocity.IsNearlyZero())
    {
        return;
    }

    FVector ReflectedVelocity = FMath::GetReflectionVector(CurrentVelocity, Hit.Normal);
    ReflectedVelocity = ReflectedVelocity.GetSafeNormal() * CurrentVelocity.Size();

    ProjectileMovement->Velocity = ReflectedVelocity;
    ProjectileMovement->UpdateComponentVelocity();
}



// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APongBall::StartGame()
{
	if (HasAuthority())
    {
		SetActorLocation(InitialLocation);
    
        FVector InitialDirection = FVector::ZeroVector;

        InitialDirection.X = FMath::RandBool() ? 1.0f : -1.0f;
        InitialDirection.Y = FMath::FRandRange(-1.0f, 1.0f);
        InitialDirection.Z = 0.0f;
        InitialDirection.Normalize();

        ProjectileMovement->Velocity = InitialDirection * ProjectileMovement->InitialSpeed;
    }
}
