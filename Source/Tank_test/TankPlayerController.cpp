// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogTankPawn, All, All)

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::onMoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::onMoveRight);
	InputComponent->BindAxis("RotationRight", this, &ATankPlayerController::onRotationRight);

	bShowMouseCursor = true;
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

void ATankPlayerController::onRotationRight(float Amount)
{
	if (PlayerTank)
		PlayerTank->RotateRight(Amount);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = CastChecked<ATankPawn>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector MousePosition, MouseDirection;
	DeprojectMousePositionToWorld(MousePosition, MouseDirection);

	auto Z = FMath::Abs(PlayerTank->GetActorLocation().Z - MousePosition.Z);
	MouseWorldPosition = MousePosition - MouseDirection * Z / MouseDirection.Z;

	//Draw shpere debug
	//DrawDebugSphere(GetWorld(), MousePosition, 3, 16, FColor::Green);
	//DrawDebugLine(GetWorld(), MousePosition, MousePosition+MouseDirection*5000, FColor::Red);
	
	//V tochke peresechenia treisami
	//FHitResult Result;
	//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Result);
	//DrawDebugSphere(GetWorld(), Result.ImpactPoint, 3, 16, FColor::Blue);
}
