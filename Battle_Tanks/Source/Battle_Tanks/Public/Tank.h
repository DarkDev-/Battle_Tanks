// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurretComponent;
class AProjectile;

UCLASS()
class BATTLE_TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* aiming_component;

public:	
	void AimAt(const FVector location);

	UFUNCTION(BlueprintCallable)
	void Fire();

private:
	// In cm
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launch_speed = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectile_bp;

	UTankBarrel* barrel;

	float reload_time = 2.0f;
	float last_fire_time = 0.0f;
	
};
