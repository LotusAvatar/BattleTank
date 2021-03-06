// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank track is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_U4_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()


public:

	/*UFUNCTION(BlueprintCallable, Category = Input)
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
*/
	
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float throttle);

	UPROPERTY(EditDefaultsOnly)
		float trackMaxDrivingForce = 40000000.0f; // Assume 40 tonne tank, and 1g acceleration
};
