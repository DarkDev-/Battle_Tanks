// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

#include "Tank.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(const FVector location, const float launch_speed)
{
	if (!barrel)
		return;

	FVector launch_velocity;
	const FVector start_location = barrel->GetSocketLocation(FName("Launch_Location"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, launch_velocity, start_location, location, launch_speed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		const auto aim_direction = launch_velocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at: %s"), *aim_direction.ToString());
	}

}