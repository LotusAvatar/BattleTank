// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class UTankAimingComponent;

UCLASS()
class BATTLETANK_U4_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;

private:
	FVector playerLocation;
	float acceptanceRadius = 3000.0f;

	void Initialize();
};
