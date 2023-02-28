// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLGamePlayInterface.h"
#include "ARLItemContainer.generated.h"

UCLASS()
class ARL_TOMLOOMAN_API AARLItemContainer : public AActor, public IARLGamePlayInterface
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	AARLItemContainer();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CleanUpPtr();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

};
