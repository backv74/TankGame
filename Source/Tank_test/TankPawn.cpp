// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/InputComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogTankPawn, All, All)

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	TankBody = CreateDefaultSubobject<USkeletalMeshComponent>("TankBody");
	TankBody->SetupAttachment(RootComponent);

	TankTurret = CreateDefaultSubobject<USkeletalMeshComponent>("TankTurret");
	TankTurret->SetupAttachment(TankBody);

	ArmComponent = CreateDefaultSubobject<USpringArmComponent>("ArmComponent");
	ArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(ArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

void ATankPawn::MoveForward(float Scale)
{
	MoveSpeedForward = Scale;
}

void ATankPawn::MoveRight(float Scale)
{
	MoveSpeedRight = Scale;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto NewLocationForward = GetActorLocation() + MoveSpeedForward * DeltaTime * MovementSpeed * GetActorForwardVector();
	SetActorLocation(NewLocationForward);
	const auto NewLocationRight = GetActorLocation() + MoveSpeedRight * DeltaTime * MovementSpeed * GetActorRightVector();
	SetActorLocation(NewLocationRight);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


