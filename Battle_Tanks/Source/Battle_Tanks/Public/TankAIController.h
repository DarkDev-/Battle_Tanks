// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLE_TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;
	
private:
	APawn* player_tank;
	APawn* controlled_tank;
	UTankAimingComponent* aiming_component;

	// How close in radius (CM) the AI can be to the player before it stops
	UPROPERTY(EditDefaultsOnly)
	float acceptance_radius = 3000.0f;
};
