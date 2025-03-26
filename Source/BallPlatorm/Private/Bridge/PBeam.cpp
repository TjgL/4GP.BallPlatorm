// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge/PBeam.h"

#include "Bridge/PConnector.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "PhysicsField/PhysicsFieldComponent.h"


APBeam::APBeam()
{
	PrimaryActorTick.bCanEverTick = true;
}

FVector2D APBeam::GetForceAtConnector(APConnector* Connector)
{
	if (Start != nullptr && End != nullptr && Length0 > 0.f)
	{
		const FVector2D StartPos = FVector2D(Start->GetActorLocation().X, Start->GetActorLocation().Z);
		const FVector2D EndPos = FVector2D(End->GetActorLocation().X, End->GetActorLocation().Z);
		FVector2D Length = StartPos - EndPos;
		FVector2D Displacement = Length.GetSafeNormal() * (Length.Size() - Length0);

		FVector2D ForceBeam = Displacement * Stiffness;
		FVector2D ForceGravity = FVector2D(0.f, UPhysicsSettings::Get()->DefaultGravityZ);

		if (ForceBeamMax > 0.f)
		{
			ForceFactor = ForceBeam.Size() / ForceBeamMax;
		}

		if (Start == Connector)
			return (ForceBeam * -1.f) + ForceGravity / 2.f;
		else if (End == Connector)
			return ForceBeam + ForceGravity / 2.f;
	}
	
	return FVector2D::ZeroVector;
}

void APBeam::BeginPlay()
{
	Super::BeginPlay();
	
}

void APBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

