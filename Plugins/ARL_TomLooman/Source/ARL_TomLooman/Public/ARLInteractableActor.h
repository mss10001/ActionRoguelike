// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLGamePlayInterface.h"
#include "ARLInteractableActor.generated.h"

class USphereComponent;

UCLASS()
class ARL_TOMLOOMAN_API AARLInteractableActor : public AActor, public IARLGamePlayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARLInteractableActor();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TSoftObjectPtr<AActor> DependentInteractableActor;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

};
