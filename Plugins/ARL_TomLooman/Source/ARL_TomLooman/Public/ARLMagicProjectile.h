// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLProjectile.h"
#include "ARLMagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARL_TOMLOOMAN_API AARLMagicProjectile : public AARLProjectile
{
	GENERATED_BODY()
	
public:

	virtual void PostInitializeComponents() override;

	UFUNCTION() // Delegates must have UFUNCTION macro !!!!!
	void OnSphereCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
