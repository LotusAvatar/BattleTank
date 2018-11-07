// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomHeaders.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
class ATank; // Forward Declaration

UCLASS()
class BATTLETANK_U4_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float crossHairXLocation;
	UPROPERTY(EditAnywhere)
		float crossHairYLocation;
	UPROPERTY(EditAnywhere)
		float lineTraceRange = 1000000.0f;

	void Initialize();
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& outHitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& outHitLocation) const;
};
