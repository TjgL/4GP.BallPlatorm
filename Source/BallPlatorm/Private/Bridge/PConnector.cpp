// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge/PConnector.h"


APConnector::APConnector()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APConnector::BeginPlay()
{
	Super::BeginPlay();
	
}

void APConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsAnchor && MassSumStored > 0.f)
	{
		FVector2D Acc = ForceSumStored / MassSumStored;
		
	}
}

