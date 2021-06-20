// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	
	Move();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMovementDirection); //this calls CalculateMovementDirection providing it with params from -1 to 1 when we move forward
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateMovementRotation);		 //this calls CalculateMovementRotation providing it with params from -1 to 1 when we rotate
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
