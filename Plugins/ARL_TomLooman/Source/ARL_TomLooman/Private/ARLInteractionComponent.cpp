// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLInteractionComponent.h"
#include "ARLGamePlayInterface.h"

// Sets default values for this component's properties
UARLInteractionComponent::UARLInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UARLInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UARLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UARLInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	TObjectPtr<AActor> MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	/*FHitResult Hit;
	bool bBlockiongHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);*/

	TArray<FHitResult> Hits;
	float Radius = 30.f;
	FCollisionShape CollisionSphere;
	CollisionSphere.SetSphere(Radius);
	bool bBlockiongHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, CollisionSphere); 

	FColor LineColor = bBlockiongHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		TObjectPtr<AActor> HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UARLGamePlayInterface>())
			{
				TObjectPtr<APawn> MyPawn = Cast<APawn>(MyOwner);
			
				IARLGamePlayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 16, LineColor, false, 2.f, 0, 1.f);
	}
		
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);

}

