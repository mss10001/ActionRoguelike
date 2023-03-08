// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLExplosive.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AARLExplosive::AARLExplosive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName(/* UCollisionProfile::PhysicsActor_ProfileName */ "PhysicsActor");
	SetRootComponent(MeshComp);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(MeshComp);

	// Leaving this on applies small constant force via COMPONENT 'tick' (Optional)
	RadialForceComp->SetAutoActivate(false);

	// Initialize some force values
	RadialForceComp->Radius = 400.f;
	RadialForceComp->ImpulseStrength = 1200.f;  // Alternative: 200000.0 if bImpulseVelChange = false

	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	RadialForceComp->bImpulseVelChange = true;
	
	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void AARLExplosive::PostInitializeComponents()
{	
	Super::PostInitializeComponents();	

	MeshComp->OnComponentHit.AddDynamic(this, &AARLExplosive::OnExplosiveHit);
}


void AARLExplosive::OnExplosiveHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnExplosiveHit triggered"));

	// %s string
	// %f float/double
	// %i integer

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, OtherComp: %s at game time: %f"), *GetNameSafe(OtherActor), *GetNameSafe(OtherComp), GetWorld()->TimeSeconds);
	UE_LOG(LogTemp, Warning, TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	// Detailed info on logging in ue4
	// https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-messages-to-yourself-during-runtime.html

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.Location, CombinedString, nullptr, FColor::Green, 5.f, true);
}



void AARLExplosive::CleanUpPtr()
{
	MeshComp = nullptr;
	RadialForceComp = nullptr;
}

void AARLExplosive::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CleanUpPtr();
	Super::EndPlay(EndPlayReason);
}

void AARLExplosive::Destroyed()
{
	CleanUpPtr();
	Super::Destroyed();
}

