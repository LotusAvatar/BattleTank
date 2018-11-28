// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "CustomHeaders.h"
#include "TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float amount)
{
	if (!ensure(leftTrack) || !ensure(rightTrack))
		return;

	leftTrack->SetThrottle(amount);
	rightTrack->SetThrottle(amount);
}

void UTankMovementComponent::IntendTurnRight(float amount)
{
	if (!ensure(leftTrack) || !ensure(rightTrack))
		return;

	leftTrack->SetThrottle(amount);
	rightTrack->SetThrottle(-amount);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();

	float dotProduct = FVector::DotProduct(tankForward, aiForwardIntention);
	float crossProduct = FVector::CrossProduct(tankForward, aiForwardIntention).Z;

	IntendMoveForward(dotProduct);
	IntendTurnRight(crossProduct);
	//UE_LOG(LogTemp, Warning, TEXT("Tank: %s, MoveVelocity: %s"), *tankName, *MoveVelocity.ToString());

}

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

