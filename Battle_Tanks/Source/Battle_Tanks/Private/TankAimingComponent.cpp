// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "TankBarrel.h"
#include "TankTurretComponent.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::AimAt(const FVector location)
{
	if (!ensure(barrel))
		return;

	FVector launch_velocity;
	const FVector start_location = barrel->GetSocketLocation(FName("Launch_Location"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, launch_velocity, start_location, location, launch_speed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		aim_direction = launch_velocity.GetSafeNormal();
		MoveBarrel(aim_direction);
	}
}

void UTankAimingComponent::MoveBarrel(FVector direction)
{
	if (!ensure(barrel && turret))
		return;

	auto barrel_rotator = barrel->GetForwardVector().Rotation();
	auto aim_as_rotator = direction.Rotation();
	auto delta_rotator = aim_as_rotator - barrel_rotator;

	barrel->Elevate(delta_rotator.Pitch);

	// Make sure that the turret always use the shortest path when aiming
	if (FMath::Abs(delta_rotator.Yaw) < 180.0f)
		turret->Rotate(delta_rotator.Yaw);
	else
		turret->Rotate(-delta_rotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(barrel))
		return false;

	return !barrel->GetForwardVector().Equals(aim_direction, 0.01f);
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if ((GetWorld()->GetTimeSeconds() - last_fire_time) < reload_time)
		firing_state = EFiringState::RELOADING;
	else if (IsBarrelMoving())
		firing_state = EFiringState::AIMING;
	else
		firing_state = EFiringState::LOCKED;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	last_fire_time = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Initialize(UTankBarrel* barrel_component, UTankTurretComponent* turret_component)
{
	barrel = barrel_component;
	turret = turret_component;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(barrel))
		return;

	if (firing_state != EFiringState::RELOADING)
	{
		if (!ensure(projectile_bp))
			return;

		const FVector barrel_location = barrel->GetSocketLocation(FName("Launch_Location"));
		const FRotator barrel_rotation = barrel->GetSocketRotation(FName("Launch_Location"));
		const auto projectile = GetWorld()->SpawnActor<AProjectile>(projectile_bp, barrel_location, barrel_rotation);

		projectile->LaunchProjectile(launch_speed);
		last_fire_time = GetWorld()->GetTimeSeconds();
	}
}
