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
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BluePrintImplementableEvent)
	void GameOver(bool PlayerWon);
};
