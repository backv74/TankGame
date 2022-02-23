// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPawn.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANK_TEST_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Velocity = 300.0f;
	
public:
	virtual void SetupInputComponent() override;

	void onMoveForward(float Amount);
	void onMoveRight(float Amount);

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ATankPawn* PlayerTank;
};