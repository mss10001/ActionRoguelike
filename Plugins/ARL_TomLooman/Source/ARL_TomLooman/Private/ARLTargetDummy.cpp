// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLTargetDummy.h"
#include "../Public/ARLAttributesComponent.h"

// Sets default values
AARLTargetDummy::AARLTargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	SetRootComponent(MeshComp);

	AttributeComp = CreateDefaultSubobject<UARLAttributesComponent>("AttributeComp");
}

void AARLTargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	AttributeComp->OnHealthChanged.AddDynamic(this, &AARLTargetDummy::OnHealthChanged);
}

void AARLTargetDummy::OnHealthChanged(AActor* InstigatorActor, UARLAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}



