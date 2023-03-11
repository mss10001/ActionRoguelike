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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UARLAttributesComponent> AttributeComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	UFUNCTION()
	void OnHealthChanged( AActor* InstigatorActor, UARLAttributesComponent* OwningComp, float NewHealth, float Delta);
public:
	void PostInitializeComponents() override;

};
