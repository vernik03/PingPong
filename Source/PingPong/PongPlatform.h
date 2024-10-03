// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <EnhancedInputLibrary.h>
#include "PongPlatform.generated.h"

UCLASS()
class PINGPONG_API APongPlatform : public APawn
{
	GENERATED_BODY()

public:
	APongPlatform();

protected:
	virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    class UStaticMeshComponent* PlatformMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputMappingContext* InputMappingContext;

private:
    UFUNCTION()
    void MovePlatform(const FInputActionValue& Value);

    UPROPERTY(Replicated)
    float PlatformPositionY = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Input")
    float InputMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Input")
    float Limiter = 600.0f;

    UFUNCTION(Server, Reliable)
    void MovePlatformOnServer(float MovementValue);

    void MovePlatform(float MovementValue);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
