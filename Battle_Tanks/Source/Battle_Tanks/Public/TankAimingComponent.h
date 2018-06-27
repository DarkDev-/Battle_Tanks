// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	RELOADING,
	AIMING,
	LOCKED,
	OUT_OF_AMMO
};

class UTankBarrel;
class UTankTurretComponent;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* barrel_component, UTankTurretComponent* turret_component);

	void SetBarrel(UTankBarrel* barrel_to_set) { if(barrel_to_set) barrel = barrel_to_set; }
	void SetTurret(UTankTurretComponent* turret_to_set) { if(turret_to_set) turret = turret_to_set; }

	void AimAt(const FVector location);
	void MoveBarrel(FVector direction);
	bool IsBarrelMoving();
	
	UFUNCTION(BlueprintCallable)
	void Fire();

	EFiringState GetFiringState() const { return firing_state; }

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetCurrentAmmo() const { return current_ammo; }

private:
	UTankBarrel* barrel;
	UTankTurretComponent* turret;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectile_bp;

	// In cm
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launch_speed = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int current_ammo = 30; // Int because unreal is weird and doesn't support unsigned in bp

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reload_time = 2.0f;

	float last_fire_time = 0.0f;

	FVector aim_direction;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "States")
	EFiringState firing_state;
};
