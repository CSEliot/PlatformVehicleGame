// Fill out your copyright notice in the Description page of Project Settings.

#include "cartest.h"
#include "BestCar.h"


// Sets default values
ABestCar::ABestCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABestCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABestCar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABestCar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

