// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;

	bIgnoreInstigatorWhenMoving = true;
	
}

void AARLProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	TObjectPtr<AActor> MyInstigator = Cast<AActor>(GetInstigator());
	
	if (ensure(IsValid(MyInstigator)))
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
	if (ensure(IsValid(this) && IsValid(ImpactVFX)))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		Destroy();
	}
}

void AARLProjectile::CleanUpPtr()
{
	SphereComp = nullptr;
	MovementComp = nullptr;
	EffectComp = nullptr;
}

void AARLProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
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
