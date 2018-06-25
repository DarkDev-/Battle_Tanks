// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void MoveForward(float throttle);

	UFUNCTION(BlueprintCallable, Category = Input)
	void TurnRight(float throttle);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void InitializeComponents(UTankTrackComponent* track_left, UTankTrackComponent* track_right);

protected:
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrackComponent* tank_track_left;
	UTankTrackComponent* tank_track_right;
	
	
};
