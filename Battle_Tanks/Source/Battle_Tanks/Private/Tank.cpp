// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("SLOTH: Creating %s"), *GetName());
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	current_health = starting_health;
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATank::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage_to_apply = FMath::Clamp(Damage, 0.0f, current_health);

	current_health -= damage_to_apply;
	if (current_health <= 0.0f)
		on_death.Broadcast();

	return damage_to_apply;
}
