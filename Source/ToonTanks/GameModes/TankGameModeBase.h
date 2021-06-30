// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	int32 GetTargetTurretAmount();

	int32 TargetTurrets;
	APawnTank *PlayerTank;

public:
	void ActorDied(AActor *DeadActor);

protected:
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Game Loop") //means that this variable can only be read in blueprints and the default value can be changed before starting the game
	int32 StartDelay = 4;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BluePrintImplementableEvent)
	void GameOver(bool PlayerWon);
};
