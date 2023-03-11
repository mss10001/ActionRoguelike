// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "ARLAttributesComponent.h"

AARLMagicProjectile::AARLMagicProjectile()
{
	SphereComp->SetSphereRadius(20.f);
	InitialLifeSpan = 5.f;
	DamageAmount = 20.f;

}

void AARLMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARLMagicProjectile::OnSphereCompBeginOverlap);
}

void AARLMagicProjectile::OnSphereCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor) && (OtherActor != GetInstigator()))
	{
		TObjectPtr<UARLAttributesComponent> AttributeComp = Cast<UARLAttributesComponent>(OtherActor->GetComponentByClass(UARLAttributesComponent::StaticClass()));
		if (IsValid(AttributeComp))
		{
			AttributeComp->ApplyHealthChange(-DamageAmount);

			Destroy();
		}
	}
}
