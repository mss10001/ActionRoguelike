// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARLExampleChar.generated.h"


class USpringArmComponent;
class UCameraComponent;

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

	UPROPERTY(EditAnywhere, Category = "DebugHelpers")
	bool DebugActive = false;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void DrawDebugDirections();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
