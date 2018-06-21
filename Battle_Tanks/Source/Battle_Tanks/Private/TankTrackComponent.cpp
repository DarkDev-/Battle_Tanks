// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"


void UTankTrackComponent::SetThrottle(float throttle)
{
	throttle = FMath::Clamp(throttle, -1.0f, 1.0f);
	UE_LOG(LogTemp, Warning, TEXT("%s wroom: %f"), *GetName(), throttle);
}
