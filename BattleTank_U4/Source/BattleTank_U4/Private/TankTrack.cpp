// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "CustomHeaders.h"

void UTankTrack::SetThrottle(float throttle)
{
	FString name = GetName();

	FVector forceApllied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApllied, forceLocation);
}
