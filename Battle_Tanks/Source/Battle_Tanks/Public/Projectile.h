// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLE_TANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	void LaunchProjectile(const float speed);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* collision_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* projectile_movement_component;

	UPROPERTY(VisibleAnywhere, Category = "Particles")
	UParticleSystemComponent* launch_blast;

	UPROPERTY(VisibleAnywhere, Category = "Particles")
	UParticleSystemComponent* impact_blast;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	URadialForceComponent* explosion_force;

private:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle destroy_projectile_handle;
	void OnDestroyProjectileEnd();
	float destroy_delay = 2.0f;

};
