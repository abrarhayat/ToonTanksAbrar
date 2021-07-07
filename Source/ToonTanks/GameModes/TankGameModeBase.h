// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	void HandleGameOverOnTimeOut();
	int32 GetTargetTurretAmount();
	FTimerHandle EndGameTimerHandle;

	UPROPERTY(BlueprintReadonly, Category = "Score", meta = (AllowPrivateAccess = "true"))
	int32 TurretsDestroyed = 0;
	int32 TargetTurrets;
	APawnTank *PlayerTank;
	APlayerControllerBase *PlayerControllerRef;

public:
	void ActorDied(AActor *DeadActor);

protected:
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Game Loop") //means that this variable can only be read in blueprints and the default value can be changed before starting the game
	int32 StartDelay = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Loop")
	int32 GameTimeLeft = 75;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BluePrintImplementableEvent)
	void GameOver(bool PlayerWon);
};
