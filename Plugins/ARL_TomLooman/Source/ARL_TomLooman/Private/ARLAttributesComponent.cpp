// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLAttributesComponent.h"

// Sets default values for this component's properties
UARLAttributesComponent::UARLAttributesComponent()
{
	Health = 100.f;
	MaxHealth = 100.f;
}

bool UARLAttributesComponent::IsAlive() const
{
	return Health > 0.f;
}

bool UARLAttributesComponent::ApplyHealthChange(float Delta)
{
	float OldHealth = Health;
	Health = FMath::Clamp((Health + Delta), 0.f, MaxHealth);
	float NewDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, NewDelta);

	return true;
}


