// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VillagesCustomPC.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGESGOLDEDITION_API AVillagesCustomPC : public APlayerController
{
	GENERATED_BODY()

public:

		UFUNCTION(BlueprintImplementableEvent)
		void PawnLeavingGame() override;
	
};
