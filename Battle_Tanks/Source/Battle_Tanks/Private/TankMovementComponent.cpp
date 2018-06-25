// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

void UTankMovementComponent::MoveForward(float throttle)
{
	throttle = FMath::Clamp(throttle, -1.0f, 1.0f);

	tank_track_left->SetThrottle(throttle);
	tank_track_right->SetThrottle(throttle);
}

void UTankMovementComponent::TurnRight(float throttle)
{
	throttle = FMath::Clamp(throttle, -1.0f, 1.0f);

	tank_track_left->SetThrottle(throttle);
	tank_track_right->SetThrottle(-throttle);
}

void UTankMovementComponent::InitializeComponents(UTankTrackComponent* track_left, UTankTrackComponent* track_right)
{
	if (!track_left || !track_right)
		return;

	tank_track_left = track_left;
	tank_track_right = track_right;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	const FVector tank_forward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	const FVector ai_forward_intention = MoveVelocity.GetSafeNormal();

	auto throttle = FVector::DotProduct(tank_forward, ai_forward_intention);
	MoveForward(throttle);

	auto turn_throttle = FVector::CrossProduct(tank_forward, ai_forward_intention).Z;
	TurnRight(turn_throttle);
}
