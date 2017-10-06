// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/World.h"
#include "CoreMinimal.h"
///To access DOREPLIFETIME macro
#include "Net/UnrealNetwork.h"
#include "Components/SceneComponent.h"
#include "AimPredictionSC.generated.h"

UENUM()
enum class EAimCommand : uint8
{
	verticalAim,
	horizontalAim
};



USTRUCT()
struct FtoServerAimData
{
	GENERATED_BODY()

	UPROPERTY()
	EAimCommand command;
	UPROPERTY()
	float value;
	UPROPERTY()
	FRotator recentRotation;
};


UCLASS(Blueprintable, ClassGroup=(Villages), meta=(BlueprintSpawnableComponent) )
class VILLAGESGOLDEDITION_API UAimPredictionSC : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimPredictionSC();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;
	

	///Must call from client only!
	UFUNCTION(BlueprintCallable, Category = "Villages")
		void addPitch(float value);

		void addRotation(EAimCommand command, float value);

		///server helper
		bool checkIsTolerance(FRotator target);

		void smoothRotation();
		

	UFUNCTION(Server, Reliable, WithValidation)
		void SERVER_makeRotation(FtoServerAimData data);

	UFUNCTION(Client, Reliable)
		void CLIENT_sendCorrection(FRotator correctedRotation);

	///Must call from client only!
	UFUNCTION(BlueprintCallable, Category = "Villages")
		void addYaw(float value);
	
	UFUNCTION()
		void OnRep_setNewCurrentRotation();

	///Properties

	UPROPERTY(ReplicatedUsing = OnRep_setNewCurrentRotation)
		FRotator replicatedRotation;

		FRotator nextRotation;
	

	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
