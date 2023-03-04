// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLProjectile.h"
#include "ARLDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARL_TOMLOOMAN_API AARLDashProjectile : public AARLProjectile
{
	GENERATED_BODY()
	
public:

	AARLDashProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonationDelay;

	// Handle to cancel timer if we hit something
	FTimerHandle TimerHandle_DelayedDonate;

	// Base class using BluprintNativeEvent, so we must override the Explode_Implementation not the Explode()
	void Explode_Implementation() override;

	void TeleportInstigator();

	virtual void BeginPlay() override;

};
