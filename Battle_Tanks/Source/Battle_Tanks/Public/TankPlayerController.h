// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLE_TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void SetAimingComponent(UTankAimingComponent* aiming_component);

public:
	void Tick(float DeltaTime) override;

private:
	void AimTowardsCrosshair();
	bool GetLookAtLocation(FVector& hit_location) const;
	bool GetLookAtDirection(FVector& look_direction) const;
	FVector2D GetCrosshairLocation() const;

	UPROPERTY(EditDefaultsOnly)
	float crosshair_x_location = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float crosshair_y_location = 0.33f;

	// In cm	
	UPROPERTY(EditDefaultsOnly)
	float trace_range = 1000000.0f;

	UTankAimingComponent* aiming_component;
	APawn* controlled_tank;

	void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnDeath();
};
