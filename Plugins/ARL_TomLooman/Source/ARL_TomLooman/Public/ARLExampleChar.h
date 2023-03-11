// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ARLExampleChar.generated.h"


class USpringArmComponent;
class UCameraComponent;
class AARLProjectile;
class UARLInteractionComponent;
class UARLAttributesComponent;


UCLASS()
class ARL_TOMLOOMAN_API AARLExampleChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARLExampleChar();


	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;

	/* Particle System played during attack animation */
	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<UParticleSystem> CastingEffect;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UARLInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UARLAttributesComponent> AttributeComp;

	UPROPERTY(EditAnywhere, Category = "DebugHelpers")
	bool DebugActive = false;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AARLProjectile> MagicProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AARLProjectile> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AARLProjectile> DashProjectileClass;


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

	void StartAttackEffect();

	void SpawnProjectile(TSubclassOf<AARLProjectile> ProjectileToSpawn, bool bIncludePhysicsBodyCheck = true);

	void PrimaryInteract();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void DrawDebugDirections();

	UFUNCTION()
	void OnHealthChanged( AActor* InstigatorActor, UARLAttributesComponent* OwningComp, float NewHealth, float Delta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
