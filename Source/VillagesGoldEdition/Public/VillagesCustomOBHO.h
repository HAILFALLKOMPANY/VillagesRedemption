// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconHostObject.h"
#include "VillagesCustomOBHO.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class VILLAGESGOLDEDITION_API AVillagesCustomOBHO : public AOnlineBeaconHostObject
{
	GENERATED_BODY()

public:
	AVillagesCustomOBHO(const FObjectInitializer & ObjectInitializer);

	//Apply new changes on BeaconTypeName and ActorClass from configs variable
	UFUNCTION(BlueprintCallable, Category = "Villages")
		void applyBeaconCurrentActorClass();

	UFUNCTION()
		void OnClientConnected(AOnlineBeaconClient * NewClientActor, UNetConnection * ClientConnection) override;
	UFUNCTION(BlueprintCallable, Category = "Villages")
		void DisconnectClient(AOnlineBeaconClient * ClientActor) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Villages")
		void WhenNewClientSpawned(AOnlineBeaconClient * NewClientActor);
	
	UPROPERTY(EditDefaultsOnly, Category = "Villages")
		TSubclassOf < AOnlineBeaconClient > configClientBeaconActorClass;
	
};
