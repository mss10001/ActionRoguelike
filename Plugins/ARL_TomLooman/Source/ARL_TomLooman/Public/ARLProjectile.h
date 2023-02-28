// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ARL_TOMLOOMAN_API AARLProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARLProjectile();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> MovementComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UParticleSystemComponent> EffectComp;
	
	virtual void BeginPlay() override;

	virtual void CleanUpPtr();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

};