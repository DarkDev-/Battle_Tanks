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
	void IntendMoveForward(float throttle);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void InitializeComponents(UTankTrackComponent* track_left, UTankTrackComponent* track_right);


private:
	UTankTrackComponent* tank_track_left;
	UTankTrackComponent* tank_track_right;
	
	
};
