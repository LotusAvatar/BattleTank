// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "CustomHeaders.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Elevate: %f"), relativeSpeed);

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);

	float elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;

	float elevation = FMath::Clamp<float>(rawNewElevation, minElevationDegree, maxElevationDegree);

	//FString DebugMsg = FString::Printf(TEXT("Elevation: %s"), *FString::SanitizeFloat(elevation));
	//GEngine->AddOnScreenDebugMessage(6, 0.0f, FColor::Green, DebugMsg);

	SetRelativeRotation(FRotator(elevation, 0.0f, 0.0f));
}

