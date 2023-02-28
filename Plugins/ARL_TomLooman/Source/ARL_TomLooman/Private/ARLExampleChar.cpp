// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLExampleChar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ARLProjectile.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ARLInteractionComponent.h"

// Sets default values
AARLExampleChar::AARLExampleChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UARLInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false; // false means don't turn the pawn with the controller
}

// Called when the game starts or when spawned
void AARLExampleChar::BeginPlay()
{
	Super::BeginPlay();
	
}


void AARLExampleChar::DrawDebugDirections()
{
	// --- Rotation Visualization
	const float DrawScale = 100.f;
	const float Thickness = 5.f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.f;
	// Set line end indirection of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.f);
	// Draw Actor's C
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.f);
	// Draw 'Controller' Rotation  that possess this pawn
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.f, 0, Thickness);

}

// Called every frame
void AARLExampleChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DebugActive)
	{
		DrawDebugDirections();
	}

}

// Called to bind functionality to input
void AARLExampleChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AARLExampleChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARLExampleChar::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AARLExampleChar::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AARLExampleChar::PrimaryInteract);
}

void AARLExampleChar::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void AARLExampleChar::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void AARLExampleChar::PrimaryAttack()
{
	if (ProjectileClass)
	{
		FActorSpawnParameters SpawnParams = FActorSpawnParameters();
		SpawnParams.Instigator = this;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		const FVector ProjectileLocation = GetActorLocation() + (GetActorForwardVector() * 50.f);
		const FRotator ProjectileDirection = GetControlRotation();
		GetWorld()->SpawnActor<AActor>(ProjectileClass, HandLocation, ProjectileDirection, SpawnParams);
	}
}

void AARLExampleChar::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}
