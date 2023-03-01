// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ARLExampleChar.generated.h"


class USpringArmComponent;
class UCameraComponent;
class AARLProjectile;
class UARLInteractionComponent;

UCLASS()
class ARL_TOMLOOMAN_API AARLExampleChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARLExampleChar();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UARLInteractionComponent> InteractionComp;

	UPROPERTY(EditAnywhere, Category = "DebugHelpers")
	bool DebugActive = false;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AARLProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackMontage;

	FTimerHandle TimerHandle_PrimaryAttack;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PrimaryAttack();

	void PrimaryAttack_TimeElapsed();

	void PrimaryInteract();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void DrawDebugDirections();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
