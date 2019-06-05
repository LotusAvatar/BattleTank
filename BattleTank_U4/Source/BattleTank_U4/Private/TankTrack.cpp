// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "CustomHeaders.h"


//void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
//{
//	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	/*FString trackName = GetName();
//	UE_LOG(LogTemp, Warning, TEXT("Ticking s%"), trackName);*/
//	
//	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//	FVector correctionAcceleration = -slippageSpeed * GetRightVector();
//
//	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//	FVector correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2.0f;
//	tankRoot->AddForce(correctionForce);
//}

void UTankTrack::SetThrottle(float throttle)
{
	FString name = GetName();

	FVector forceApllied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApllied, forceLocation);
}
