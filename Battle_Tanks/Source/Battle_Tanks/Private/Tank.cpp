// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "Engine/World.h"

#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

#include "Projectile.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("SLOTH: Creating %s"), *GetName());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATank::AimAt(const FVector location)
{
	if (!aiming_component)
		return;

	aiming_component->AimAt(location, launch_speed);
}

void ATank::Fire()
{
	bool is_reloaded = (GetWorld()->GetTimeSeconds() - last_fire_time) > reload_time;

	if (barrel && is_reloaded)
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectile_bp, barrel->GetSocketLocation(FName("Launch_Location")), barrel->GetSocketRotation(FName("Launch_Location")));
		projectile->LaunchProjectile(launch_speed);
		last_fire_time = GetWorld()->GetTimeSeconds();
	}
}
