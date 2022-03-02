// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Cannon.generated.h"

UENUM()
enum class ECannonType : uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use projectiles"),
	FireTrace = 1 UMETA(DisplayName = "Use trace")
};

UCLASS()
class TANK_TEST_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CannonBody;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	int ProjectileCount = 10;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	int TraceCount = 10;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType Type = ECannonType::FireProjectile;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	int AutoShootNumbers = 3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float AutoShootDelay = 3.f;

	void Shoot();
	void AutoShoot();
	void AutoShootNumber();
	void Reload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ResetShootState();
	void ResetAutoShootState();
	void ReloadTime();

	FTimerHandle TimerHandle;
	FTimerHandle TimerHandleAutoShoot;
	FTimerHandle TimerHandleReload;

	bool bReadyToShoot = true;
	bool bReadyToAutoShoot = true;
	
	int count = 0;

};
