// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float amount)
{
	if (!leftTrack || !rightTrack)
		return;

	leftTrack->SetThrottle(amount);
	rightTrack->SetThrottle(amount);
}

void UTankMovementComponent::IntendTurnRight(float amount)
{
	if (!leftTrack || !rightTrack)
		return;

	leftTrack->SetThrottle(amount);
	rightTrack->SetThrottle(-amount);
}

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

