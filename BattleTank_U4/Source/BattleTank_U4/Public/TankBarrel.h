// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)/*, hidecategories = (Collision)*/)
class BATTLETANK_U4_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float relativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxDegreesPerSecond = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxElevationDegree = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float minElevationDegree = 0.0f;
};
