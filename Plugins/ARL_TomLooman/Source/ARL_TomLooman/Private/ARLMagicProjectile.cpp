// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "ARLAttributesComponent.h"

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
			AttributeComp->ApplyHealthChange(-20.f);

			Destroy();
		}
	}
}
