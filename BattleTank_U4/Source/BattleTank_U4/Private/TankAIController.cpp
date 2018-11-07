// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player possessing: %s"), *(PlayerTank->GetName()));
	}

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		playerLocation = GetPlayerTank()->GetActorLocation();
		GetControlledTank()->AimAt(playerLocation);
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);

}



