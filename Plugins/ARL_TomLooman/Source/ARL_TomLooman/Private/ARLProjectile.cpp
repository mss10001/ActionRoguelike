// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AARLProjectile::AARLProjectile()
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
	EffectComp->SetupAttachment(GetRootComponent());

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(GetRootComponent());

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;

	bIgnoreInstigatorWhenMoving = true;

	ImpactShakeInnerRadius = 0.0f;
	ImpactShakeOuterRadius = 1500.0f;
	
}

void AARLProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	TObjectPtr<AActor> MyInstigator = Cast<AActor>(GetInstigator());
	
	if (IsValid(MyInstigator))
	{
		SphereComp->IgnoreActorWhenMoving(MyInstigator, bIgnoreInstigatorWhenMoving);
	}
}

void AARLProjectile::OnSphereCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Error, TEXT("OtherActor %s"), *GetNameSafe(OtherActor));
	Explode();
}

void AARLProjectile::Explode_Implementation()
{
	// Check to make sure we aren't already being 'destroyed'
	// Adding ensure to see if we encounter this situation at all
	if (ensure(IsValid(this)))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		UGameplayStatics::PlaySoundAtLocation(this, ImpactSoundCue, GetActorLocation());
		
		UGameplayStatics::PlayWorldCameraShake(this, ImpactCameraShake, GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);

		Destroy();
	}
}

void AARLProjectile::CleanUpPtr()
{
	SphereComp = nullptr;
	MovementComp = nullptr;
	EffectComp = nullptr;
	AudioComp = nullptr;
}

void AARLProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Explode();
	CleanUpPtr();
	Super::EndPlay(EndPlayReason);
}


void AARLProjectile::Destroyed()
{
	CleanUpPtr();
	Super::Destroyed();
}

void AARLProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComp->OnComponentHit.AddDynamic(this, &AARLProjectile::OnSphereCompHit);
}


