// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Engine/World.h"

#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	controlled_tank = GetPawn();
	player_tank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if(ensure(player_tank))
		aiming_component = controlled_tank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(player_tank && controlled_tank && aiming_component))
		return;

	MoveToActor(player_tank, acceptance_radius);
	
	aiming_component->AimAt(player_tank->GetActorLocation());
	if(aiming_component->GetFiringState() == EFiringState::LOCKED)
		aiming_component->Fire();
}