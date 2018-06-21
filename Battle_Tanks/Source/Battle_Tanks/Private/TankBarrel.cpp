// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float relative_speed)
{
	relative_speed = FMath::Clamp(relative_speed, -1.0f, 1.0f);
	float elevation_change = relative_speed * max_degrees_per_second * GetWorld()->GetDeltaSeconds();
	float raw_new_elevation = RelativeRotation.Pitch + elevation_change;
	auto elevation = FMath::Clamp(raw_new_elevation, min_elevation, max_elevation);

	SetRelativeRotation(FRotator(elevation, 0.0f, 0.0f));
}
