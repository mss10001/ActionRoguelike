// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLBlackHoleProjectile.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


AARLBlackHoleProjectile::AARLBlackHoleProjectile()
{
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(GetRootComponent());

	EObjectTypeQuery ObjectType = UEngineTypes::ConvertToObjectType(ECC_Pawn);	
	ForceComp->RemoveObjectTypeToAffect(ObjectType);
	ForceComp->Radius = 1000.f;
	ForceComp->ForceStrength = -600000.f;
	SphereComp->SetSphereRadius(80.f);
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	
	SetLifeSpan(5.f);
}

void AARLBlackHoleProjectile::OnSphereCompOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

void AARLBlackHoleProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARLBlackHoleProjectile::OnSphereCompOverlap);
}
