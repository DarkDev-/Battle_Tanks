// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Engine/World.h"

#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ensure(GetPlayerTank()))
	{
		MoveToActor(GetPlayerTank(), acceptance_radius);

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		GetControlledTank()->Fire();
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
