// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLDashProjectile.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AARLDashProjectile::AARLDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonationDelay = 0.2f;

	MovementComp->InitialSpeed = 6000.f;
}

void AARLDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("Instigator %s"), *GetNameSafe(GetInstigator()));
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDonate, this, &AARLDashProjectile::Explode, DetonationDelay);
}

void AARLDashProjectile::Explode_Implementation()
{
	// Clear timer if the Explode was already called through another source like OnSphereCompHit
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	// Deactivates the projectile particles
	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AARLDashProjectile::TeleportInstigator,TeleportDelay);

	// Skip base implementation (Super::Explode_Implementation) as it destroy the actor immediatly but we need time to finish the second timer
}

void AARLDashProjectile::TeleportInstigator()
{
	TObjectPtr<AActor> ActorToTeleport = GetInstigator();

	if (ensure(ActorToTeleport))
	{
		// Keep instigator rotation or it may end up jarring
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}

	Destroy();
}
