// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_U4_API AProjectile : public AActor
{
	 GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed);

private:

	UProjectileMovementComponent* projectileMovementComponent = nullptr;
};
