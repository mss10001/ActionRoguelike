// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLTargetDummy.generated.h"

class UARLAttributesComponent;

UCLASS()
class ARL_TOMLOOMAN_API AARLTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARLTargetDummy();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UARLAttributesComponent> AttributeComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UFUNCTION()
	void OnHealthChanged( AActor* InstigatorActor, UARLAttributesComponent* OwningComp, float NewHealth, float Delta);
public:
	void PostInitializeComponents() override;

};
