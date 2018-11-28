// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked 
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret; 
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_U4_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel * barrelToSet, UTankTurret * turretToSet);

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable)
		void Fire();

	UTankBarrel* Barrel = nullptr;
		
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState firingState = EFiringState::Aiming;

private:
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void GetProjectileBP_reference();

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectile_BP;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadedTimeInSeconds = 3.0f;

	float lastFireTime = 0;

	FVector aimDirection;

	UTankTurret* Turret = nullptr;

	void MoveTowards(FVector launchVelocity);
};
