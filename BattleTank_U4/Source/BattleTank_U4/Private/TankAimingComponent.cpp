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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	GetProjectileBP_reference();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	lastFireTime += DeltaTime;

	FString DebugMsg1 = FString::Printf(TEXT("lastFireTime: %f"), lastFireTime);
	GEngine->AddOnScreenDebugMessage(2, 0.0f, FColor::Green, DebugMsg1);

	if (lastFireTime < reloadedTimeInSeconds)
		firingState = EFiringState::Reloading;
	else if (IsBarrelMoving())
		firingState = EFiringState::Aiming;
	else
		firingState = EFiringState::Locked;
}

void UTankAimingComponent::GetProjectileBP_reference()
{
	//Gets the reference of projectile_BP directly from the content folder
	FString projectile_BP_ref = TEXT("Blueprint'/Game/tank/Projectile_BP.Projectile_BP'");
	UObject * loadedObject = StaticLoadObject(UObject::StaticClass(), nullptr, *projectile_BP_ref);
	UBlueprint* castedBlueprint = Cast<UBlueprint>(loadedObject);

	if (!ensure(castedBlueprint))
		return;

	if (ensure(castedBlueprint->GeneratedClass->IsChildOf(AProjectile::StaticClass())))
		projectile_BP = *castedBlueprint->GeneratedClass;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;
	
	FVector barrelForward = Barrel->GetForwardVector();
	return !barrelForward.Equals(aimDirection, 0.01f);
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
		MoveTowards(outLaunchVelocity);
	}
	else
	{
	/*	FString DebugMsg1 = FString::Printf(TEXT("No Solution Found!"));
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, DebugMsg1);*/
	}
}

void UTankAimingComponent::Fire()
{
	if (!(firingState == EFiringState::Reloading))
	{
		if (!ensure(Barrel && projectile_BP))
		{
			return;
		}

		FVector spawnLocation = Barrel->GetSocketLocation(FName("ProjectileStartSocket"));
		FRotator spawnRotation = Barrel->GetSocketRotation(FName("ProjectileStartSocket"));
		AProjectile * projectile = GetWorld()->SpawnActor<AProjectile>(projectile_BP, spawnLocation, spawnRotation);
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = 0.0f;
		firingState = EFiringState::Reloading;
	}
}

void UTankAimingComponent::MoveTowards(FVector launchVelocity)
{
	aimDirection = launchVelocity.GetSafeNormal();

	if (!ensure(Barrel || Turret))
		return;

	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator- barrelRotator;

	Turret->Rotate(deltaRotator.Yaw);
	Barrel->Elevate(deltaRotator.Pitch);
}
