// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "CustomHeaders.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel * barrelToSet, UTankTurret * turretToSet)
{
	Barrel = barrelToSet;
	Turret = turretToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (!ensure(Barrel || Turret))
		return;

	FVector outLaunchVelocity(0);
	FVector startLocation = Barrel->GetSocketLocation(FName("ProjectileStartSocket"));
	//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s Start Location: %s "), *hitLocation.ToString(), *startLocation.ToString());

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, launchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveTowards(aimDirection);
	}
	else
	{
		FString DebugMsg1 = FString::Printf(TEXT("No Solution Found!"));
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, DebugMsg1);
	}
}

void UTankAimingComponent::Fire()
{
	/*if (!ensure(TankAimingComponent))
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
	}*/
}

void UTankAimingComponent::MoveTowards(FVector aimDirection)
{
	if (!ensure(Barrel || Turret))
		return;

	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator- barrelRotator;

	Turret->Rotate(deltaRotator.Yaw);
	Barrel->Elevate(deltaRotator.Pitch);
}
