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

	aiming_component = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetBarrel(UTankBarrel* barrel_component)
{
	if (barrel_component)
	{
		aiming_component->SetBarrel(barrel_component);
		barrel = barrel_component;
	}
}

void ATank::SetTurret(UTankTurretComponent* turret_component)
{
	if (turret_component)
		aiming_component->SetTurret(turret_component);
}

void ATank::AimAt(const FVector location)
{
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
