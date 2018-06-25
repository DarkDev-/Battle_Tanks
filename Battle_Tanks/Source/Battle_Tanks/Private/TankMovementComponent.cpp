// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

void UTankMovementComponent::IntendMoveForward(float throttle)
{
	throttle = FMath::Clamp(throttle, -1.0f, 1.0f);

	tank_track_left->SetThrottle(throttle);
	tank_track_right->SetThrottle(throttle);
}

void UTankMovementComponent::InitializeComponents(UTankTrackComponent* track_left, UTankTrackComponent* track_right)
{
	if (!track_left || !track_right)
		return;

	tank_track_left = track_left;
	tank_track_right = track_right;
}
