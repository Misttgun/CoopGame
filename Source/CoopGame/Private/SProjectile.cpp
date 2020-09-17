// Fill out your copyright notice in the Description page of Project Settings.

#include "SProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASProjectile::ASProjectile()
{
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
}


void ASProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &ASProjectile::Explode, 1, false);
}

void ASProjectile::Explode()
{
	// Draw a collision sphere
	DrawDebugSphere(GetWorld(), GetActorLocation(), 200, 50, FColor::Cyan, true, 2.0f);

	FVector MyLocation = GetActorLocation();

	AActor* MyOwner = GetOwner();
	if(MyOwner)
		UGameplayStatics::ApplyRadialDamage(GetWorld(), 100, MyLocation, 200, DamageType, TArray<AActor*>(), this, MyOwner->GetInstigatorController());

	// Play particle system
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, MyLocation);
	}

	Destroy();
}

