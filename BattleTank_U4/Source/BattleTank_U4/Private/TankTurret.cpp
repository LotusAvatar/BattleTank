// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "CustomHeaders.h"


void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);

	float rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rotation = RelativeRotation.Yaw + rotationChange;


	//FString DebugMsg = FString::Printf(TEXT("Elevation: %s"), *FString::SanitizeFloat(elevation));
	//GEngine->AddOnScreenDebugMessage(6, 0.0f, FColor::Green, DebugMsg);

	SetRelativeRotation(FRotator(0.0f, rotation, 0.0f));
}

