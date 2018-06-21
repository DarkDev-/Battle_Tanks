// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurretComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void SetBarrel(UTankBarrel* barrel_to_set) { if(barrel_to_set) barrel = barrel_to_set; }
	void SetTurret(UTankTurretComponent* turret_to_set) { if(turret_to_set) turret = turret_to_set; }

public:	
	void AimAt(const FVector location, const float launch_speed);
	void MoveBarrel(FVector direction);

private:
	UTankBarrel* barrel;
	UTankTurretComponent* turret;
};
