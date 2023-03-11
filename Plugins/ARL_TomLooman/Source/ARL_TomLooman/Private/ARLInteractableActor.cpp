// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLInteractableActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AARLInteractableActor::AARLInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	SphereComp->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
	SphereComp->SetSphereRadius(50.f);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SphereComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DependentInteractableActor = nullptr;
}

// Called when the game starts or when spawned
void AARLInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARLInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARLInteractableActor::Interact_Implementation(APawn* InstigatorPawn)
{
	//Handling TSoftObjectPtr and call dependent actor interface
	if (DependentInteractableActor.IsValid())
	{
		if (DependentInteractableActor->Implements<UARLGamePlayInterface>())
		{
			IARLGamePlayInterface::Execute_Interact(DependentInteractableActor.Get(), InstigatorPawn);
		}
		
	}
}


