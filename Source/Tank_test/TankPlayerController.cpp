// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPawn.h"
#include "TankPlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogTankPawn, All, All)

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::onMoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::onMoveRight);
}

void ATankPlayerController::onMoveForward(float Amount)
{
	UE_LOG(LogTankPawn, Display, TEXT("Move forward: %f"), Amount);
	//VelocityVector.X = Amount;
	if (PlayerTank)
	PlayerTank->MoveForward(Amount);

}

void ATankPlayerController::onMoveRight(float Amount)
{
	UE_LOG(LogTankPawn, Display, TEXT("Move right: %f"), Amount);
	//VelocityVector.Y = Amount;
	if (PlayerTank)
	PlayerTank->MoveRight(Amount);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = CastChecked<ATankPawn>(GetPawn());
}
