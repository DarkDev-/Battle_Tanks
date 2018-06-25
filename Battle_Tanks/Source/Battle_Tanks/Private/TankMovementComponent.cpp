// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float _throw)
{
	_throw = FMath::Clamp(_throw, -1.0f, 1.0f);
	UE_LOG(LogTemp, Warning, TEXT("%f"), _throw);
}



