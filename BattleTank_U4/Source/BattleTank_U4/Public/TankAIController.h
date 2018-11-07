// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomHeaders.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class ATank; // Forward Declaration

UCLASS()
class BATTLETANK_U4_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank * GetControlledTank() const;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	ATank * GetPlayerTank() const;

private:
	FVector playerLocation;
};
