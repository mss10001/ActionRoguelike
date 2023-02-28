// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLItemContainer.h"

// Sets default values
AARLItemContainer::AARLItemContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void AARLItemContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARLItemContainer::CleanUpPtr()
{
	BaseMesh = nullptr;
}

void AARLItemContainer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CleanUpPtr();
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AARLItemContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARLItemContainer::Destroyed()
{
	CleanUpPtr();
	Super::Destroyed();
}

void AARLItemContainer::Interact_Implementation(APawn* InstigatorPawn)
{

}

