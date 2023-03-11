// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLInteractableTimedActor.h"
#include "Components/SphereComponent.h"

AARLInteractableTimedActor::AARLInteractableTimedActor()
{
	TimeToReactivate = 3.f;
}

void AARLInteractableTimedActor::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	GetWorldTimerManager().SetTimer(TimerHandle_Reactivation, this, &AARLInteractableTimedActor::ReactivationTimerElapsed, TimeToReactivate);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetVisibility(false);

}

void AARLInteractableTimedActor::ReactivationTimerElapsed()
{
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComp->SetVisibility(true);
}
