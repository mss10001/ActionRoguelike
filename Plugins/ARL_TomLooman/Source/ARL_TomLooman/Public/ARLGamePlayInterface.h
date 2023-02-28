// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ARLGamePlayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UARLGamePlayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARL_TOMLOOMAN_API IARLGamePlayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Implementation in inherited class ( InheritedClass implements it so: void Interact_Implementation(APawn* InstigatorPawn);
	// 
	// Execution: call Execute_Interact(UObject* O, APawn* InstigatorPawn); on this interface by using static funtion or cast owner to interface
	// Examples:	- Cast<IARLGamePlayInterface>(O)->Execute_InterfaceOptionalFunction(O, Instigator);
	//				- IARLGamePlayInterface::Execute_InterfaceOptionalFunction(O, Instigator);
	// 
	// Check if Object implemented the Interface: if (Owner->Implements<UARLGamePlayInterface>()){} ATTENTION: Here the UARLGamePlayInterface and not the IARLGamePlayInterface will be used
	// 
	// take also a look into "UARLInteractionComponent::PrimaryInteract()" and "AARLItemChest::Interact_Implementation(APawn* InstigatorPawn)"
	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
