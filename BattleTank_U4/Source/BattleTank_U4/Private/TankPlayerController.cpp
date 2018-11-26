// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "CustomHeaders.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::Initialize()
{
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
	crossHairXLocation = 0.5f;
	crossHairYLocation = 0.33333f;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
		return;

	FVector outHitLocation;

	if (GetSightRayHitLocation(outHitLocation))
		GetControlledTank()->AimAt(outHitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & outHitLocation) const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation = FVector2D(viewportSizeX * crossHairXLocation, viewportSizeY * crossHairYLocation);
	
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		if (GetLookVectorHitLocation(lookDirection, outHitLocation))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *outHitLocation.ToString());
			return true;	
		}
		outHitLocation = FVector(0);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector & lookDirection) const
{
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector & outHitLocation) const
{
	FHitResult hitResult;
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (lookDirection * lineTraceRange);

	FString DebugMsg1 = FString::Printf(TEXT("endLocation: %s"), *endLocation.ToString());
	GEngine->AddOnScreenDebugMessage(2, 0.0f, FColor::Green, DebugMsg1);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility))
	{
		outHitLocation = hitResult.Location;
		return true;
	}
	return false;
}