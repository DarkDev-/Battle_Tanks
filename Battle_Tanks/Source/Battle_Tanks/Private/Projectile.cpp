// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "Components/StaticMeshComponent.h"

#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

#include "TimerManager.h"

AProjectile::AProjectile()
{
	collision_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	collision_mesh->SetNotifyRigidBodyCollision(true);
	collision_mesh->SetVisibility(false);

	SetRootComponent(collision_mesh); 

	launch_blast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Particle Component"));
	launch_blast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	impact_blast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast Particle Component"));
	impact_blast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impact_blast->bAutoActivate = false;
	
	explosion_force = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force Component"));
	explosion_force->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	projectile_movement_component = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	projectile_movement_component->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	collision_mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	launch_blast->Deactivate();
	impact_blast->Activate();

	explosion_force->FireImpulse();

	SetRootComponent(impact_blast);
	collision_mesh->DestroyComponent();

	// TODO: Add self to actors to ignore
	UGameplayStatics::ApplyRadialDamage(this, projectile_damage, GetActorLocation(), explosion_force->Radius, UDamageType::StaticClass(), TArray<AActor*>());

	GetWorld()->GetTimerManager().SetTimer(destroy_projectile_handle, this, &AProjectile::OnDestroyProjectileEnd, destroy_delay, false);
}

void AProjectile::OnDestroyProjectileEnd()
{
	this->Destroy();
}

void AProjectile::LaunchProjectile(const float speed)
{
	projectile_movement_component->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectile_movement_component->Activate();
}

