// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AARLMagicProjectile::AARLMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");

	/* // For manual setting collisions
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn);*/

	// more convenient setting collision through setting up new profile in project settings
	SphereComp->SetCollisionProfileName("Projectile"); 
	SetRootComponent(SphereComp);	

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void AARLMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARLMagicProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SphereComp = nullptr;
	MovementComp = nullptr;
	EffectComp = nullptr;

	Super::EndPlay(EndPlayReason);
}

void AARLMagicProjectile::Destroyed()
{
	SphereComp = nullptr;
	MovementComp = nullptr;
	EffectComp = nullptr;

	Super::Destroyed();
}

// Called every frame
void AARLMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



