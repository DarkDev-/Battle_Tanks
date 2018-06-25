// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"


void UTankTrackComponent::SetThrottle(float throttle)
{
	throttle = FMath::Clamp(throttle, -1.0f, 1.0f);
	UE_LOG(LogTemp, Warning, TEXT("%s wroom: %f"), *GetName(), throttle);

	auto applied_force = GetForwardVector() * throttle * max_force;
	auto force_location = GetComponentLocation();
	auto root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	root->AddForceAtLocation(applied_force, force_location);
}
