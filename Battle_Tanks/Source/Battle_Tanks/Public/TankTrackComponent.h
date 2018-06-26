// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANKS_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UTankTrackComponent();

	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);

	// Max force per track in Newton
	UPROPERTY(EditDefaultsOnly)
	float max_force = 700000.0f;

private:
	UStaticMeshComponent* root;
};
