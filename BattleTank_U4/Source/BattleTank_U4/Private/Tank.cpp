// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "CustomHeaders.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::Fire()
{
	if (!ensure(TankAimingComponent)) 
		return;

	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime > reloadedTimeInSeconds);

	if (isReloaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Firing!"));
		FVector spawnLocation = TankAimingComponent->Barrel->GetSocketLocation(FName("ProjectileStartSocket"));
		FRotator spawnRotation = TankAimingComponent->Barrel->GetSocketRotation(FName("ProjectileStartSocket"));
		AProjectile * projectile = GetWorld()->SpawnActor<AProjectile>(projectile_BP, spawnLocation, spawnRotation);
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector hitLocation)
{
	if (!ensure(TankAimingComponent))
		return;
	
	TankAimingComponent->AimAt(hitLocation, launchSpeed);
}

// Called when the game starts or when spawned

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

