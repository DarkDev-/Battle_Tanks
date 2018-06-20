// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
		return;

	FVector hit_location;
	if (GetLookAtLocation(hit_location))
		UE_LOG(LogTemp, Warning, TEXT("Looking at %s"), *hit_location.ToString());
}

bool ATankPlayerController::GetLookAtLocation(FVector& hit_location) const
{
	FVector look_direction;
	if (GetLookAtDirection(look_direction))
		UE_LOG(LogTemp, Warning, TEXT("%s"), *look_direction.ToString());

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
