// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTurret.h"
#include "ToonTanks/Components/HealthComponent.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController()); //We are calling APawn::GetController() to get AController and casting it to APlayerController
}

void APawnTank::HandleDestruction()
{
	//Calling the Base HandleDestruction from PawnBase to play effects
	Super::HandleDestruction();
	//Hide PLayer, TODO create a separate function to do this
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();

	Move();

	/* This is cause the turret to move automatically towards the first Turret it finds
	TArray<AActor *> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, APawnTurret::StaticClass(), FoundActors);
	RotateTurretToTarget(FoundActors[0]->GetActorLocation()); 
	*/

	//Moving the turret to where we place the cursor on the mouse
	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult); //Here, Channel is the visibility channel, we are not using complex tracing and saving our hit result in TraceHitResult
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurretToTarget(HitLocation);
	}
	// UHealthComponent *HealthComponent = FindComponentByClass<UHealthComponent>();
	// UE_LOG(LogTemp, Warning, TEXT("Player Health: %f"), HealthComponent->Health);
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMovementDirection); //this calls CalculateMovementDirection providing it with params from -1 to 1 when we move forward
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateMovementRotation);		 //this calls CalculateMovementRotation providing it with params from -1 to 1 when we rotate
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);				 // BindAction is similar to BindAxis except it reacts to single actions like pressed / released
}

void APawnTank::CalculateMovementDirection(float Value)
{
	MovementDirection = FVector(Value * MovementSpeed * GetWorld()->DeltaTimeSeconds, 0, 0); //movement only in x-axis
}

void APawnTank::CalculateMovementRotation(float Value)
{
	float MovementRotationAmount;
	MovementRotationAmount = Value * MovementSpeed * GetWorld()->DeltaTimeSeconds;
	MovementRotation = FQuat(FRotator(0, MovementRotationAmount, 0)); //movement only in y-axis //FQuat is an advanced version of FRotator which prevents gimbel locking
}

void APawnTank::Move()
{
	AddActorLocalOffset(MovementDirection, true); //the second arg determines whether it should calculate collision before moving
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(MovementRotation, true);
}
