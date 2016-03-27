// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GravityRegion.generated.h"

UCLASS()
class CARTEST_API AGravityRegion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravityRegion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "GravityRegion") UBoxComponent* GetRegion();
	UFUNCTION(BlueprintCallable, Category = "GravityRegion") UArrowComponent* GetGravityArrow();
	UFUNCTION(BlueprintCallable, Category = "GravityRegion") float GetGravityStrength();

	UFUNCTION(BlueprintCallable, Category = "GravityRegion") void SetRegion(UBoxComponent* newregion);
	UFUNCTION(BlueprintCallable, Category = "GravityRegion") void SetGravityArrow(UArrowComponent* newarrow);
	UFUNCTION(BlueprintCallable, Category = "GravityRegion") void SetGravityStrength(float newstrength);

	UPROPERTY(EditAnywhere) UBoxComponent* Region;
	UPROPERTY(EditAnywhere) UArrowComponent* GravityDirection;

	UPROPERTY(EditAnywhere) float GravityStrength;
	
};
