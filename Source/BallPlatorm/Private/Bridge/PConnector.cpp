// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge/PConnector.h"

#include "Bridge/PBeam.h"


APConnector::APConnector()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void APConnector::CalculateForces()
{
	for (int i = Beams.Num() - 1; i >= 0; i--)
	{
		APBeam* Beam = Beams[i];
		if (Beam != nullptr)
		{
			ForceSumStored += Beam->GetForceAtConnector(this);
		}
	}
}

void APConnector::Disconnect(APBeam* APBeam)
{
	Beams.Remove(APBeam);
}

void APConnector::BeginPlay()
{
	Super::BeginPlay();
	
}

void APConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ForceSumStored = FVector::ZeroVector;

	if (!bIsAnchor)
	{
		CalculateForces();
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + ForceSumStored, FColor::Red);
		Mesh->AddForce(ForceSumStored);
	}
}

