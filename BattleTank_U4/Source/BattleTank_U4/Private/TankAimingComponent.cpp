// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * barrelToSet)
{
	Barrel = barrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float lauchSpeed)
{
	if (!Barrel)
		return;

	FVector outLaunchVelocity(0);
	FVector startLocation = Barrel->GetSocketLocation(FName("ProjectileStartSocket"));
	//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s Start Location: %s "), *hitLocation.ToString(), *startLocation.ToString());


	if (UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, lauchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		FString tankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *tankName, *aimDirection.ToString());
	}
}

