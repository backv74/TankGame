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
	if (!bReadyToShoot || ProjectileCount == 0 || TraceCount == 0 || GetWorld()->GetTimerManager().IsTimerActive(TimerHandleReload))
		return;

	switch (Type)
	{
	case ECanonType::FireProjectile:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("PIU")));
		if (ProjectileCount != 0) { ProjectileCount--; }
		break;
	case ECanonType::FireTrace:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString(TEXT("PUF")));
		if (TraceCount != 0) { TraceCount--; }
		break;
	default:
		break;
	}
	bReadyToShoot = false;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ACannon::ResetShootState), 1 / FireRate, false);
}

void ACannon::AutoShoot()
{
	if (!bReadyToAutoShoot || !bReadyToShoot || ProjectileCount == 0 || 
		TraceCount == 0 || GetWorld()->GetTimerManager().IsTimerActive(TimerHandleReload))
		return;
	
	bReadyToAutoShoot = false;
	bCannonAmmoFull = true;
	
	switch (Type)
	{
	case ECanonType::FireProjectile:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("AutoPIU")));
		if (ProjectileCount != 0) { ProjectileCount--; }
		break;
	case ECanonType::FireTrace:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString(TEXT("AutoPUF")));
		if (TraceCount != 0) { TraceCount--; }
		break;
	default:
		break;
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandleAutoShoot, 
		FTimerDelegate::CreateUObject(this, &ACannon::ResetAutoShootState), AutoShootDelay, bCannonAmmoFull);
}


void ACannon::Reload()
{
	if (TraceCount != 10 || ProjectileCount != 10) { 
		bReadyToShoot = false;
		bReadyToAutoShoot = false;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleReload, 
			FTimerDelegate::CreateUObject(this, &ACannon::ReloadTime), 2.f, false);
	}
}

void ACannon::RocketShoot()
{
	if (!bReadyToRocket)
		return;
	switch (TypeRocket)
	{
	case ECanonRocketType::FireRocketProjectile:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("RocketPIU")));
		//if (ProjectileCount != 0) { ProjectileCount--; }
		break;
	case ECanonRocketType::FireRocketTrace:
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString(TEXT("RocketPUF")));
		//if (TraceCount != 0) { TraceCount--; }
		break;
	default:
		break;
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandleRocket, 
		FTimerDelegate::CreateUObject(this, &ACannon::ResetRocketState), 1 / FireRate, false);
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
	GEngine->AddOnScreenDebugMessage(123456, 10, FColor::Blue, FString::Printf(TEXT("%u"), ProjectileCount));
	GEngine->AddOnScreenDebugMessage(1234567, 10, FColor::Blue, FString::Printf(TEXT("%u"), TraceCount));
	GEngine->AddOnScreenDebugMessage(1234, 10, FColor::Green, FString::Printf(TEXT("%f"), GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandleAutoShoot)));
	GEngine->AddOnScreenDebugMessage(123, 10, FColor::Orange, FString::Printf(TEXT("Reload %f"), GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandleReload)));
}

void ACannon::ResetShootState()
{
	bReadyToShoot = true;
}

void ACannon::ResetAutoShootState()
{
	if (AutoShootNumbers != 1)
	{
		AutoShootNumbers--;
		bReadyToAutoShoot = true;
		AutoShoot();
	}
	else {
		AutoShootNumbers = 3;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandleAutoShoot);
		bReadyToAutoShoot = true;
		bCannonAmmoFull = false;
	}
}

void ACannon::ResetRocketState()
{
	bReadyToRocket = true;
}

void ACannon::ReloadTime()
{
	bReadyToShoot = true;
	bReadyToAutoShoot = true;
	TraceCount = 10;
	ProjectileCount = 10;
}

