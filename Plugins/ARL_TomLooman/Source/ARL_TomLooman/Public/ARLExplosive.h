// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLExplosive.generated.h"

class URadialForceComponent;

UCLASS()
class ARL_TOMLOOMAN_API AARLExplosive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARLExplosive();

protected:

	// For explosion simulation
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URadialForceComponent> RadialForceComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	virtual void CleanUpPtr();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	// Must be marked with UFUNCTION in order to 'bind' the event
	UFUNCTION()
	void OnExplosiveHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

public:


	virtual void PostInitializeComponents() override;

public:
	virtual void Destroyed() override;

};