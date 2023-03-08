// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLAttributesComponent.h"

// Sets default values for this component's properties
UARLAttributesComponent::UARLAttributesComponent()
{
	Health = 100;
}

bool UARLAttributesComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}


