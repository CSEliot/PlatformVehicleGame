// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GravityRegion.h"
#include "newcar.generated.h"

UCLASS()
class CARTEST_API Anewcar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Anewcar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
	void Hit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Stay(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void UnHit(class AActor * OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Turn(float AxisValue);
	void Strafe(float AxisValue);
	void Jump();
	
	UPROPERTY(EditAnywhere) UCapsuleComponent* Root;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* Model;
	UPROPERTY(EditAnywhere) USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere) UCameraComponent* Camera;
	UPROPERTY(EditAnywhere) UArrowComponent* Up;
	UPROPERTY(EditAnywhere) UArrowComponent* Forward;
	UPROPERTY(EditAnywhere) UArrowComponent* Right;

	UPROPERTY(EditAnywhere) AGravityRegion* First;

	UPROPERTY(EditAnywhere) float AccelRate;
	UPROPERTY(EditAnywhere) float MaxVelocity;
	UPROPERTY(EditAnywhere) float JumpPower;
	UPROPERTY(EditAnywhere) float TurnRate;

	FVector Gravity;
	FVector TurnInput;
	FVector StrafeInput;

	float angle;

	bool OnTheGround;
	bool JumpNextFrame;

};
