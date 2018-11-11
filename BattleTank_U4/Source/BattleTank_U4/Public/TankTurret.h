// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = (Collision))
class BATTLETANK_U4_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float relativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxDegreesPerSecond = 25.0f;
};
