// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    TargetTurrets = GetTargetTurretAmount();
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor *DeadActor)
{
    if (DeadActor == PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player, %s died!"), *DeadActor->GetName());
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    }
    else if (APawnTurret *DestroyedTurret = Cast<APawnTurret>(DeadActor)) //if this case is accessible, it will return true
    {
        UE_LOG(LogTemp, Warning, TEXT("Turret, %s died!"), *DeadActor->GetName());
        DestroyedTurret->HandleDestruction();
        if (--TargetTurrets == 0) //decreasing Target Turret amount by 1 and checking against it
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart()
{
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    GameStart(); //This is a function to be implemented in Blueprint
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon); //This is a function to be implemented in Blueprint
}

int32 ATankGameModeBase::GetTargetTurretAmount()
{
    TArray<AActor *> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}
