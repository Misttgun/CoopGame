// Fill out your copyright notice in the Description page of Project Settings.

#include "SGrenadeLauncher.h"
#include "SProjectile.h"

void ASGrenadeLauncher::Fire()
{
	AActor* MyOwner = GetOwner();

	if (MyOwner && ProjectileClass)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

		// Spawn the projectile at the muzzle
		GetWorld()->SpawnActor<ASProjectile>(ProjectileClass, MuzzleLocation, EyeRotation, ActorSpawnParams);

	}
}
