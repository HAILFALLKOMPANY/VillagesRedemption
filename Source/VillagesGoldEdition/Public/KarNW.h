// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "KarNW.generated.h"


/**
 *
 */


UCLASS()
class VILLAGESGOLDEDITION_API UKarNW : public UWheeledVehicleMovementComponent4W
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "VehicleSetup")
		TArray<bool> bIsDrivenWheel;

		UKarNW(const FObjectInitializer& ObjectInitializer);

	/** Allocate and setup the PhysX vehicle */
	virtual void SetupVehicleDrive(physx::PxVehicleWheelsSimData* PWheelsSimData) override;

	virtual void UpdateSimulation(float DeltaTime) override;

	
	
};
