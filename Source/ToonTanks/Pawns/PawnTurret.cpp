// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    //From the start of the game we start checking for the Firing Condition
    GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition()
{
    //If Player = null || Player is dead, stop firing
    //Check if the player is within a certain distance from the turret
    UE_LOG(LogTemp, Warning, TEXT("Checking Fire Condition"));
}
