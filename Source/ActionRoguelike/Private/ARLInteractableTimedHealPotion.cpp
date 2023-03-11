// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLInteractableTimedHealPotion.h"
#include "ARLAttributesComponent.h"

AARLInteractableTimedHealPotion::AARLInteractableTimedHealPotion()
{
	Healing = 50;
}

void AARLInteractableTimedHealPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	TObjectPtr<UARLAttributesComponent> AttribComp;
	//AttribComp = Cast<UARLAttributesComponent>(InstigatorPawn->GetComponentByClass(UARLAttributesComponent::StaticClass()));
	AttribComp = InstigatorPawn->FindComponentByClass<UARLAttributesComponent>();

	if (AttribComp && AttribComp->IsAlive() && !AttribComp->IsHealthFull())
	{
		AttribComp->ApplyHealthChange(Healing);

		// Spawn Particles and Sound?
	}

}
