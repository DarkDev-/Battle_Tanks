// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"
#include "Engine/World.h"

void UTankTurretComponent::Rotate(float relative_speed)
{
	relative_speed = FMath::Clamp(relative_speed, -1.0f, 1.0f);
	float rotation_change = relative_speed * max_degrees_per_second * GetWorld()->GetDeltaSeconds();
	float new_rotation = RelativeRotation.Yaw + rotation_change;

	SetRelativeRotation(FRotator(0.0f, new_rotation, 0.0f));
}