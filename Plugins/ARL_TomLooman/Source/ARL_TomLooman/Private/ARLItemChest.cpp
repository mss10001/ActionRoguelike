// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLItemChest.h"

AARLItemChest::AARLItemChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(GetRootComponent());

	LidRotation = (FRotator(110, 0, 0));
}

void AARLItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void AARLItemChest::Tick(float DeltaTime)
{

}

void AARLItemChest::Destroyed()
{
	CleanUpPtr();
	Super::Destroyed();
}

void AARLItemChest::CleanUpPtr()
{
	LidMesh = nullptr;
	Super::CleanUpPtr();
}

void AARLItemChest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CleanUpPtr();
	Super::EndPlay(EndPlayReason);
}


void AARLItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	if (LidMesh)
	{
		LidMesh->SetRelativeRotation(LidRotation);
	}
}

