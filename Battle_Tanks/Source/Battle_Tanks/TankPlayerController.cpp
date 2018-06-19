// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
		UE_LOG(LogTemp, Error, TEXT("Controller failed to connect with player"));
}