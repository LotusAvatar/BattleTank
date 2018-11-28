// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "CustomHeaders.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void ATankAIController::Initialize()
{
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*FString DebugMsg = FString::Printf(TEXT("ATankAIController::Tick"));
	GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, DebugMsg);*/
	
	APawn * playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn * controlledTank = GetPawn();
	UTankAimingComponent * aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();

	if (ensure(playerTank && controlledTank && aimingComponent))
	{
		MoveToActor(playerTank, acceptanceRadius);
		playerLocation = playerTank->GetActorLocation();
		aimingComponent->AimAt(playerLocation);
		aimingComponent->Fire();
	}
}


