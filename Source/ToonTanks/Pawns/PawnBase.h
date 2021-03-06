// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent; //this is a forward declaration, which will let us use this reference of the class instead of including the entire file
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) //we use the meta because we are exposing private variable to BluePrintReadOnly which will cause compile problems
	UCapsuleComponent *CapsuleComp;																				 //this is the basic collision component, this class needs to have forward declaration

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *BaseMesh; //the rest of the classes do not need forward declaration

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent *HealthComponent;

	//VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem *DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase *DeathSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UMatineeCameraShake> DeathShake;

public:
	// Sets default values for this pawn's properties
	APawnBase();

	virtual void HandleDestruction(); //the virtual keyword indicates that will method will be overridden in the child classes

	UFUNCTION(BlueprintCallable)
	float GetPawnHealth();

	UFUNCTION(BlueprintCallable)
	float GetDefaultPawnHealth();

protected:
	void RotateTurretToTarget(FVector TargetToLookAt);

	void Fire();
};
