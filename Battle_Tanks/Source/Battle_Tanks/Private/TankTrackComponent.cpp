// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"


UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();

	root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ensure(root))
		return;

	const auto slippage_speed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	const FVector correction_acceleration = -slippage_speed / DeltaTime * GetRightVector();
	const FVector correction_force = (root->GetMass()) * correction_acceleration / 2.0f;

	root->AddForce(correction_force);
}

void UTankTrackComponent::SetThrottle(float throttle)
{
	throttle = FMath::Clamp(throttle, -1.0f, 1.0f);

	const FVector applied_force = GetForwardVector() * throttle * max_force * 100.0f;
	const FVector force_location = GetComponentLocation();
	const auto root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	root->AddForceAtLocation(applied_force, force_location);
}
