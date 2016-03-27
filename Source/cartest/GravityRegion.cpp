// Fill out your copyright notice in the Description page of Project Settings.

#include "cartest.h"
#include "GravityRegion.h"


// Sets default values
AGravityRegion::AGravityRegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Region = CreateDefaultSubobject<UBoxComponent>("Region");
	Region->AttachTo(RootComponent);

	GravityDirection = CreateDefaultSubobject<UArrowComponent>("GravityDirection");
	GravityDirection->AttachTo(Region);

	GravityStrength = 980.0f;
}

// Called when the game starts or when spawned
void AGravityRegion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGravityRegion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

UBoxComponent * AGravityRegion::GetRegion()
{
	return Region;
}

UArrowComponent * AGravityRegion::GetGravityArrow()
{
	return GravityDirection;
}

float AGravityRegion::GetGravityStrength()
{
	return GravityStrength;
}

void AGravityRegion::SetRegion(UBoxComponent * newregion)
{
	Region = newregion;
}

void AGravityRegion::SetGravityArrow(UArrowComponent * newarrow)
{
	GravityDirection = newarrow;
}

void AGravityRegion::SetGravityStrength(float newstrength)
{
	GravityStrength = newstrength;
}

