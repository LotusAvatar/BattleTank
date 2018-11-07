// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * barrelToSet)
{
	Barrel = barrelToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float lauchSpeed)
{
	if (!Barrel)
		return;

	FVector outLaunchVelocity(0);
	FVector startLocation = Barrel->GetSocketLocation(FName("ProjectileStartSocket"));
	//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s Start Location: %s "), *hitLocation.ToString(), *startLocation.ToString());

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, lauchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(5.0f);
}

