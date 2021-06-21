// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    //From the start of the game we start checking for the Firing Condition
    GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0)); //getting the APawn object from the world and casting it to APawnTank
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
    if (!PlayerPawn)
    {
        return;
    }
    if (GetDistanceFromPlayerPawn() <= FiringDistanceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Firing!"));
    }
}

float APawnTurret::GetDistanceFromPlayerPawn()
{
    if (!PlayerPawn)
    {
        return 0.f;
    }
    // UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation()));
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
