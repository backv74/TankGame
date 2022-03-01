// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	

	CannonBody = CreateAbstractDefaultSubobject<UStaticMeshComponent>("CannonBody");
	CannonBody->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("ProjectilesSpawnComponent");
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void ACannon::Shoot()
{
	if (!bReadyToShoot)
		return;

	switch (Type)
	{
	case ECannonType::FireProjectile:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("PIU")));
		break;
	case ECannonType::FireTrace:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString(TEXT("PUF")));
		break;
	default:
		break;
	}
	bReadyToShoot = false;

	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ACannon::ResetShootState), 1 / FireRate, false);
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	GEngine->AddOnScreenDebugMessage(12345, 10, FColor::Blue, FString::Printf(TEXT("%f"),GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle)));
}

void ACannon::ResetShootState()
{
	bReadyToShoot = true;
}

