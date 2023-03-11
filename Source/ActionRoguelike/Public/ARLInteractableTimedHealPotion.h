// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLInteractableTimedActor.h"
#include "ARLInteractableTimedHealPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AARLInteractableTimedHealPotion : public AARLInteractableTimedActor
{
	GENERATED_BODY()
	
public:

	AARLInteractableTimedHealPotion();




	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Healing;
};
