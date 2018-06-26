// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Engine/World.h"


UTankTrackComponent::UTankTrackComponent()
	: current_throttle(0.0f)
{
}

void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrackComponent::OnHit);

	root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrackComponent::ApplySidewaysForce()
{
	if (!ensure(root))
		return;

	const auto slippage_speed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	const FVector correction_acceleration = -slippage_speed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	const FVector correction_force = (root->GetMass()) * correction_acceleration / 2.0f;

	root->AddForce(correction_force);
}

void UTankTrackComponent::ApplyForwardForce()
{
	const FVector applied_force = GetForwardVector() * current_throttle * max_force * 100.0f;
	const FVector force_location = GetComponentLocation();
	const auto root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	root->AddForceAtLocation(applied_force, force_location); // TODO: I Think it is because of this that the tank starts to fly
}

void UTankTrackComponent::SetThrottle(float throttle)
{
	current_throttle = FMath::Clamp(current_throttle + throttle, -1.0f, 1.0f);
}

void UTankTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForwardForce();
	ApplySidewaysForce();

	current_throttle = 0.0f;
}
