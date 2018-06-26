// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "Engine/World.h"

#include "TankAimingComponent.h"

#include "Projectile.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("SLOTH: Creating %s"), *GetName());
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	aiming_component = FindComponentByClass<UTankAimingComponent>();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATank::AimAt(const FVector location)
{
	if (!ensure(aiming_component))
		return;

	aiming_component->AimAt(location, launch_speed);
}

void ATank::Fire()
{
	if (!ensure(barrel))
		return;

	bool is_reloaded = (GetWorld()->GetTimeSeconds() - last_fire_time) > reload_time;

	if (is_reloaded)
	{
		const FVector barrel_location = barrel->GetSocketLocation(FName("Launch_Location"));
		const FRotator barrel_rotation = barrel->GetSocketRotation(FName("Launch_Location"));
		const auto projectile = GetWorld()->SpawnActor<AProjectile>(projectile_bp, barrel_location, barrel_rotation);

		projectile->LaunchProjectile(launch_speed);
		last_fire_time = GetWorld()->GetTimeSeconds();
	}
}
