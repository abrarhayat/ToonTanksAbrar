// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APawnBase::APawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider")); //creating an instance of a capsule component with a name, this will be the root component as this is the first declared component
	RootComponent = CapsuleComp;													   //RootComponent is inherited from AActor class

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent); //now this one will move wrt to the root component

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::RotateTurretToTarget(FVector TargetToLookAt)
{
	//Update the Turret mesh (top part) in tanks or turrets to face the TargetToLookAt
	//TurretMesh->SetWorldRotation()....
}

void APawnBase::Fire()
{
	//Get the projectile spawn point Location and Rotation -> Spawn Projectile class at Location firing towards the Rotation
}

void APawnBase::HandleDestruction()
{
	//--Univeral Functionalities--
	//Play Death Effect particle, sound and shake

	//--Child Specific Overrides--

	//--PawnTurret --Inform GameMode Turret Died-> Then Destroy self

	//--PawnTank --Inform GameMode Player Died-> Then Hide all components and stop movement input
}
