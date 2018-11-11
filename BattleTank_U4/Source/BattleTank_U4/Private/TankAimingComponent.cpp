// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "CustomHeaders.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * barrelToSet)
{
	Barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * turretToSet)
{
	Turret = turretToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float lauchSpeed)
{
	if (!Barrel || !Turret)
		return;

	FVector outLaunchVelocity(0);
	FVector startLocation = Barrel->GetSocketLocation(FName("ProjectileStartSocket"));
	//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s Start Location: %s "), *hitLocation.ToString(), *startLocation.ToString());

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, lauchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
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

void UTankAimingComponent::MoveTowards(FVector aimDirection)
{
	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator- barrelRotator;

	/*FString DebugMsg = FString::Printf(TEXT("deltaRotator: %s"), *deltaRotator.ToString());
	GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, DebugMsg);*/

	Turret->Rotate(deltaRotator.Yaw);
	Barrel->Elevate(deltaRotator.Pitch);
}
