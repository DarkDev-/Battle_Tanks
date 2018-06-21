// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void Elevate(float relative_speed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float max_degrees_per_second = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float max_elevation = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float min_elevation = 0.0f;
	
};
