// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLItemContainer.h"
#include "ARLItemChest.generated.h"

/**
 * 
 */
UCLASS()
class ARL_TOMLOOMAN_API AARLItemChest : public AARLItemContainer
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AARLItemChest();

protected:


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> LidMesh;

	UPROPERTY(EditAnywhere)
	FRotator LidRotation;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CleanUpPtr();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

};
