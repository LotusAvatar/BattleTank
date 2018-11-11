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

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetReferences(UTankBarrel * barrelToSet, UTankTurret * turretToSet)
{
	Barrel = barrelToSet;
	TankAimingComponent->SetBarrelReference(barrelToSet);
	TankAimingComponent->SetTurretReference(turretToSet);
}

void ATank::Fire()
{
	if (!Barrel)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Firing!"));
	FVector spawnLocation = Barrel->GetSocketLocation(FName("ProjectileStartSocket"));
	FRotator spawnRotation = Barrel->GetSocketRotation(FName("ProjectileStartSocket"));
	GetWorld()->SpawnActor<AProjectile>(projectile_BP, spawnLocation, spawnRotation);
}

void ATank::AimAt(FVector hitLocation)
{
	TankAimingComponent->AimAt(hitLocation, launchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

