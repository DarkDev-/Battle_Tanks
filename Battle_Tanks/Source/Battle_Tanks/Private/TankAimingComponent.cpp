// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

#include "Tank.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(const FVector location, const float launch_speed)
{
	if (!barrel)
		return;

	FVector launch_velocity;
	const FVector start_location = barrel->GetSocketLocation(FName("Launch_Location"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, launch_velocity, start_location, location, launch_speed))
	{
		const auto aim_direction = launch_velocity.GetSafeNormal();
		MoveBarrel(aim_direction);
		UE_LOG(LogTemp, Warning, TEXT("yay"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("aw"));
}

void UTankAimingComponent::MoveBarrel(FVector direction)
{
	auto barrel_rotator = barrel->GetForwardVector().Rotation();
	auto aim_as_rotator = direction.Rotation();
	auto delta_rotator = aim_as_rotator - barrel_rotator;

	barrel->Elevate(4.0f);
}