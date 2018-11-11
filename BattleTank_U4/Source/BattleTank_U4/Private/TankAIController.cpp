// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "CustomHeaders.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*FString DebugMsg = FString::Printf(TEXT("ATankAIController::Tick"));
	GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, DebugMsg);*/

	ATank * PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank * controlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		playerLocation = PlayerTank->GetActorLocation();
		controlledTank->AimAt(playerLocation);
		controlledTank->Fire();
	}
}


