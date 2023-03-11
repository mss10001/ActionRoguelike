// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLInteractableActor.h"
#include "ARLInteractableTimedActor.generated.h"

/**
 * 
 */
UCLASS()
class ARL_TOMLOOMAN_API AARLInteractableTimedActor : public AARLInteractableActor
{
	GENERATED_BODY()
	
protected:

	AARLInteractableTimedActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reactivation")
	float TimeToReactivate;

	FTimerHandle TimerHandle_Reactivation;

	UFUNCTION()
	void ReactivationTimerElapsed();

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

};
