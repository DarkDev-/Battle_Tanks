// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "Engine/World.h"

#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	controlled_tank = GetPawn();
	if(ensure(controlled_tank))
		aiming_component = controlled_tank->FindComponentByClass<UTankAimingComponent>();

	if(ensure(aiming_component))
		SetAimingComponent(aiming_component);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(controlled_tank && aiming_component))
		return;

	FVector hit_location;
	if (GetLookAtLocation(hit_location))
		aiming_component->AimAt(hit_location);
}

bool ATankPlayerController::GetLookAtLocation(FVector& hit_location) const
{
	FVector look_direction;
	if (GetLookAtDirection(look_direction))
	{
		const auto trace_start = PlayerCameraManager->GetCameraLocation();
		const auto trace_end = trace_start + (look_direction * trace_range);

		FHitResult hit;
		if (GetWorld()->LineTraceSingleByChannel(hit, trace_start, trace_end, ECC_Camera))
		{
			hit_location = hit.Location;
			return true;
		}
	}

	// Clear hit location
	hit_location = FVector(0.0f);
	return false;
}

bool ATankPlayerController::GetLookAtDirection(FVector& look_direction) const
{
	FVector world_location;
	if (DeprojectScreenPositionToWorld(GetCrosshairLocation().X, GetCrosshairLocation().Y, world_location, look_direction))
		return true;

	return false;
}

FVector2D ATankPlayerController::GetCrosshairLocation() const
{
	// Find crosshair position in pixel coordinates (hard coded af)
	int vp_x, vp_y;
	GetViewportSize(vp_x, vp_y);
	return FVector2D(vp_x * crosshair_x_location, vp_y * crosshair_y_location);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possesed_tank = Cast<ATank>(InPawn);
		if (!ensure(possesed_tank))
			return;

		possesed_tank->on_death.AddUniqueDynamic(this, &ATankPlayerController::OnDeath);
	}
}

void ATankPlayerController::OnDeath()
{
	StartSpectatingOnly(); // idk
}
