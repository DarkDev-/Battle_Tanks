// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;

UCLASS()
class BATTLE_TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	void Tick(float DeltaTime) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* barrel);

protected:
	void BeginPlay() override;

	UTankAimingComponent* aiming_component;

public:	
	void AimAt(const FVector location);

private:

	/** In cm */
	UPROPERTY(EditAnywhere, Category = Firing)
	float launch_speed = 15000.0f;
	
};
