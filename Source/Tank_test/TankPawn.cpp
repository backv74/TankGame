// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"


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

	CannonPosition = CreateDefaultSubobject<UArrowComponent>("CannonPosition");
	CannonPosition->SetupAttachment(TankTurret);

	ArmComponent = CreateDefaultSubobject<USpringArmComponent>("ArmComponent");
	ArmComponent->SetupAttachment(RootComponent);
	ArmComponent->bInheritYaw = false;
	ArmComponent->bInheritRoll = false;
	ArmComponent->bInheritPitch = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(ArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
	
}

void ATankPawn::MoveForward(float Scale)
{
	MoveScaleForwardTarget = Scale;
}

void ATankPawn::MoveRight(float Scale)
{
	MoveScaleRightTarget = Scale;
}

void ATankPawn::RotateRight(float Scale)
{
	RotationScaleTarget = Scale;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
	TankController = CastChecked<ATankPlayerController>(GetController());

	auto Transform = CannonPosition->GetComponentTransform();
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonType, Transform);
	Cannon->AttachToComponent(CannonPosition, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveTank(DeltaTime);
	RotationTank(DeltaTime);
	RotateTurret(DeltaTime);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::MoveTank(float DeltaTime)
{
	MoveScaleForwardCurrent = FMath::Lerp(MoveScaleForwardCurrent, MoveScaleForwardTarget, MovementAcceleration);
	MoveScaleRightCurrent = FMath::Lerp(MoveScaleRightCurrent, MoveScaleRightTarget, MovementAcceleration);
	const auto NewLocationForward = GetActorLocation() + 
		MoveScaleForwardCurrent * DeltaTime * MovementSpeed * GetActorForwardVector() + 
		MoveScaleRightCurrent * DeltaTime * MovementSpeed * GetActorRightVector();
	SetActorLocation(NewLocationForward);
}

void ATankPawn::RotationTank(float DeltaTime)
{
	RotationScaleCurrent = FMath::Lerp(RotationScaleCurrent, RotationScaleTarget, RotationAcceleration);
	auto Rotation = GetActorRotation();
	Rotation.Yaw += RotationScaleCurrent * RotationSpeed * DeltaTime;
	SetActorRotation(Rotation);


}

void ATankPawn::RotateTurret(float DeltaTime)
{
	if (!TankController)
		return;
	auto OldRotation = TankTurret->GetComponentRotation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(TankTurret->GetComponentLocation(), TankController->GetMousePosition());
	OldRotation.Yaw = TurretRotation.Yaw;
	TankTurret->SetWorldRotation(FMath::Lerp(TankTurret->GetComponentRotation(), OldRotation, TurretAcceleration));
}


