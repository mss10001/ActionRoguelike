// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLExampleChar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ARLProjectile.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ARLInteractionComponent.h"
#include "ARLAttributesComponent.h"
#include "Kismet/GameplayStatics.h"


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

	AttributeComp = CreateDefaultSubobject<UARLAttributesComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false; // false means don't turn the pawn with the controller

	AttackAnimDelay = 0.2f;

	TimeToHitParamName = "TimeToHit";
	HandSocketName = "Muzzle_01";
}

void AARLExampleChar::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AARLExampleChar::OnHealthChanged);
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
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AARLExampleChar::SecondaryAttack);
	PlayerInputComponent->BindAction("Action01", IE_Pressed, this, &AARLExampleChar::Action01);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AARLExampleChar::PrimaryInteract);

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

void AARLExampleChar::OnHealthChanged(AActor* InstigatorActor, UARLAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}

	if (NewHealth <= 0.f && Delta < 0.f)
	{
		TObjectPtr<APlayerController> PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			DisableInput(PC);
		}
	}
}


void AARLExampleChar::SpawnProjectile(TSubclassOf<AARLProjectile> ProjectileToSpawnClass, bool bIncludePhysicsBodyCheck)
{
	if (ensureAlways(IsValid(ProjectileToSpawnClass)))
	{
		FActorSpawnParameters SpawnParams = FActorSpawnParameters();
		SpawnParams.Instigator = this;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const FVector FireLocation = GetMesh()->GetSocketLocation(HandSocketName);
		// const FVector FireLocation = GetActorLocation() + (GetActorForwardVector() * 50.f); // Fire from center of actor (character)

		FHitResult Hit;
		FVector TraceStart = CameraComp->GetComponentLocation(); /* GetPawnViewLocation() + (GetControlRotation().Vector() * 50); */
		FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000);
		
		FCollisionShape Shape;
		Shape.SetSphere(20.f);
		
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		if (bIncludePhysicsBodyCheck)
		{
			ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
		}

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		FRotator ProjectileRotation;
		
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape, Params))
		{
			//-------------------------->>>  // same as FindLookAtRotation
			ProjectileRotation = FRotationMatrix::MakeFromX((Hit.ImpactPoint - FireLocation)).Rotator();
		}
		else
		{
			//-------------------------->>>  // same as FindLookAtRotation
			ProjectileRotation = FRotationMatrix::MakeFromX((TraceEnd - FireLocation)).Rotator();
		}

		FTransform SpawnTM = FTransform(ProjectileRotation, FireLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileToSpawnClass, SpawnTM, SpawnParams);

		//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
	}
}

void AARLExampleChar::PrimaryAttack()
{
	StartAttackEffect();

	// Fire 0.2 seconds later when the hand of the char in the montage reached fire position. Better way would be through AnimNotifier
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARLExampleChar::PrimaryAttack_TimeElapsed, AttackAnimDelay, false);
}

void AARLExampleChar::PrimaryAttack_TimeElapsed() // ############### Video 8.40 min
{
	if (ensure(IsValid(MagicProjectileClass)))
	{
		SpawnProjectile(MagicProjectileClass);
	}
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void AARLExampleChar::SecondaryAttack()
{
	StartAttackEffect();

	// Fire 0.2 seconds later when the hand of the char in the montage reached fire position. Better way would be through AnimNotifier
	GetWorldTimerManager().SetTimer(TimerHandle_Secondary, this, &AARLExampleChar::SecondaryAttack_TimeElapsed, AttackAnimDelay, false);
}

void AARLExampleChar::SecondaryAttack_TimeElapsed()
{
	if (ensure(IsValid(BlackHoleProjectileClass)))
	{
		SpawnProjectile(BlackHoleProjectileClass, false);
	}
}

void AARLExampleChar::Action01()
{
	StartAttackEffect();

	// Fire 0.2 seconds later when the hand of the char in the montage reached fire position. Better way would be through AnimNotifier
	GetWorldTimerManager().SetTimer(TimerHandle_Secondary, this, &AARLExampleChar::Action01_TimeElapsed, AttackAnimDelay, false);
}

void AARLExampleChar::Action01_TimeElapsed()
{
	if (ensure(IsValid(DashProjectileClass)))
	{
		SpawnProjectile(DashProjectileClass);
	}
}

void AARLExampleChar::StartAttackEffect()
{
	PlayAnimMontage(AttackMontage);
	UGameplayStatics::SpawnEmitterAttached(CastingEffect, GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
}

void AARLExampleChar::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}


