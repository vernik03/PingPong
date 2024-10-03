// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlatform.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Net/UnrealNetwork.h>


APongPlatform::APongPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = Root;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    PlatformMesh->SetupAttachment(Root);
}

void APongPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void APongPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = PlatformMesh->GetComponentLocation();
    FVector TargetLocation = CurrentLocation;
    TargetLocation.Y = PlatformPositionY;

    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, 5.0f);
    PlatformMesh->SetWorldLocation(NewLocation);
}

void APongPlatform::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APongPlatform::MovePlatform);
    }
}

void APongPlatform::MovePlatform(const FInputActionValue& Value)
{
    const float MovementValue = -FMath::Sign(GetActorLocation().X) * Value.Get<float>() * InputMultiplier;

    if (!Controller || MovementValue == 0.0f)
    {
        return;
    }

    if (!HasAuthority())
    {
        MovePlatformOnServer(MovementValue);
    }
    else
    {
        MovePlatform(MovementValue);
    }
}

void APongPlatform::MovePlatformOnServer_Implementation(float MovementValue)
{
    MovePlatform(MovementValue);
}

void APongPlatform::MovePlatform(float MovementValue)
{
    PlatformPositionY += MovementValue;

    PlatformPositionY = FMath::Clamp(PlatformPositionY, -Limiter, Limiter);
}

void APongPlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APongPlatform, PlatformPositionY);
}
