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
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AARLProjectile> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AARLProjectile> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AARLProjectile> Action01ProjectileClass;

	

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Secondary;
	FTimerHandle TimerHandle_Action01;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PrimaryAttack();

	void PrimaryAttack_TimeElapsed();	

	void SecondaryAttack();

	void SecondaryAttack_TimeElapsed();

	void Action01();

	void Action01_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AARLProjectile> ProjectileToSpawn);

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
