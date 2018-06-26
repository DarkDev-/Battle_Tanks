// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Engine/World.h"

#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	player_tank = GetPlayerTank();
	controlled_tank = GetControlledTank();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(player_tank))
		return;

	MoveToActor(player_tank, acceptance_radius);
	controlled_tank->AimAt(player_tank->GetActorLocation());
	controlled_tank->Fire();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
