// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLE_TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintPure, Category = "Tank")
	float GetHealthPercentage() const { return current_health / starting_health; } // I could just return the current health as max health is 100, but what if I change it? dun dun duuun

	FTankDelegate on_death;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Tank")
	float starting_health = 100;

	UPROPERTY(EditAnywhere, Category = "Tank")
	float current_health;
};
