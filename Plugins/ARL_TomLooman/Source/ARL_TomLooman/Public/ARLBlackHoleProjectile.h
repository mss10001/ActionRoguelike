// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLProjectile.h"
#include "ARLBlackHoleProjectile.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS()
class ARL_TOMLOOMAN_API AARLBlackHoleProjectile : public AARLProjectile
{
	GENERATED_BODY()
	
protected:

	AARLBlackHoleProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<URadialForceComponent> ForceComp;

	UFUNCTION()
	virtual void OnSphereCompOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	void PostInitializeComponents() override;

};
