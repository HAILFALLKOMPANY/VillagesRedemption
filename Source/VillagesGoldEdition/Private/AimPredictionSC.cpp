// Fill out your copyright notice in the Description page of Project Settings.

#include "AimPredictionSC.h"


// Sets default values for this component's properties


UAimPredictionSC::UAimPredictionSC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	SetIsReplicated(true);
	nextRotation = RelativeRotation;
}


void UAimPredictionSC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(UAimPredictionSC, replicatedRotation, COND_SkipOwner);
}



void UAimPredictionSC::addPitch(float value)
{
		if (value != 0)
		{
			addRotation(EAimCommand::verticalAim, value);
	
			///Send server command
			FtoServerAimData tempServerAimData;
			tempServerAimData.command = EAimCommand::verticalAim;
			tempServerAimData.value = value;
			tempServerAimData.recentRotation = RelativeRotation;
			SERVER_makeRotation(tempServerAimData);
		}
	

}

void UAimPredictionSC::addRotation(EAimCommand command, float value)
{
		switch (command)
		{
		case EAimCommand::verticalAim:
		{
			FRotator tempRot(value, 0, 0);
			FQuat deltaQuat(tempRot);
			AddRelativeRotation(deltaQuat);
		}
		break;
		case EAimCommand::horizontalAim:
		{
			FRotator tempRot(0, value, 0);
			FQuat deltaQuat(tempRot);
			AddRelativeRotation(deltaQuat);
		}
		break;

		default:
			break;
		}
}

bool UAimPredictionSC::checkIsTolerance(FRotator target)
{
	FQuat tempServerQ(RelativeRotation);
	FQuat tempClientQ(target);
	if (FQuat::ErrorAutoNormalize(tempServerQ, tempClientQ) > 0.3)
	{
		return false;
	}
	return true;
}

void UAimPredictionSC::smoothRotation()
{
	//FRotator tempRot = FMath::RInterpTo(currentRotation, nextRotation, GetWorld()->GetDeltaSeconds(), 3);
	FRotator tempRot = FMath::RInterpTo(RelativeRotation, nextRotation, GetWorld()->GetDeltaSeconds(), 10);
	SetRelativeRotation(FQuat(tempRot));
}



bool UAimPredictionSC::SERVER_makeRotation_Validate(FtoServerAimData data)
{
	return true;
}



void UAimPredictionSC::SERVER_makeRotation_Implementation(FtoServerAimData data)
{
	addRotation(data.command, data.value);
	if (!checkIsTolerance(data.recentRotation))
	{
		///send Correction
		CLIENT_sendCorrection(RelativeRotation);
	}
}



void UAimPredictionSC::CLIENT_sendCorrection_Implementation(FRotator correctedRotation)
{
	///apply Rotation correction 
	SetRelativeRotation(FQuat(correctedRotation));
}

void UAimPredictionSC::addYaw(float value)
{
	if (value != 0)
	{
		addRotation(EAimCommand::horizontalAim, value);

		///Send server command
		FtoServerAimData tempServerAimData;
		tempServerAimData.command = EAimCommand::horizontalAim;
		tempServerAimData.value = value;
		tempServerAimData.recentRotation = RelativeRotation;
		SERVER_makeRotation(tempServerAimData);
	}
}

void UAimPredictionSC::OnRep_setNewCurrentRotation()
{
	if (GetOwnerRole() == ROLE_SimulatedProxy)
	{
		///set and swap new rotation
		//currentRotation = RelativeRotation;
		nextRotation = replicatedRotation;
	}
}

// Called when the game starts
void UAimPredictionSC::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAimPredictionSC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///Apply Smooth Rotation if in Clients
	if (GetOwnerRole() == ROLE_SimulatedProxy)
	{
		smoothRotation();
	}
	else
	{
		///Manual set Replicated Rotation
		if (GetOwnerRole() == ROLE_Authority)
		{
			replicatedRotation = RelativeRotation;
		}
	}
}

