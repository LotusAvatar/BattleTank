// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
class ATank; // Forward Declaration
class UTankAimingComponent;

UCLASS()
class BATTLETANK_U4_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimCompRef);

private:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditDefaultsOnly)
		float crossHairXLocation;
	UPROPERTY(EditDefaultsOnly)
		float crossHairYLocation;
	UPROPERTY(EditDefaultsOnly)
		float lineTraceRange = 1000000.0f;

	void Initialize();
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& outHitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& outHitLocation) const;
};
