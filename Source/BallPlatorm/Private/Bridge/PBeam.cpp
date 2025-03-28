// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge/PBeam.h"

#include "Bridge/PConnector.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


APBeam::APBeam()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

FVector APBeam::GetForceAtConnector(APConnector* Connector)
{
	if (Start != nullptr && End != nullptr && Length0 > 0.f)
	{
		const FVector StartPos = Start->GetActorLocation();
		const FVector EndPos = End->GetActorLocation();
		const FVector Length = StartPos - EndPos;
		const FVector Displacement = Length.GetSafeNormal() * (Length.Size() - Length0);

		const FVector ForceBeam = Displacement * Stiffness;
		const FVector ForceGravity = Mesh->GetPhysicsLinearVelocity();

		if (ForceBeamMax > 0.f)
		{
			ForceFactor = ForceBeam.Size() / ForceBeamMax;
			OnForceApplied(ForceFactor);
			if (ForceFactor >= 1.0f)
			{
				BreakAll();
			}
		}

		// FString Results = FString::Printf(TEXT("Force: %s"), *ForceBeam.ToString());
		// UKismetSystemLibrary::PrintString(GetWorld(), Results, true, false, FLinearColor::Blue, 2., FName(*GetName()));
		// FString Results = FString::Printf(TEXT("Length0: %f vs Current: %f"), Length0, Length.Size());
		// UKismetSystemLibrary::PrintString(GetWorld(), Results, true, false, FLinearColor::Blue, 2., FName(*GetName()));

		if (Start == Connector)
			return (ForceBeam * -1.f) + ForceGravity / 2.f;
		else if (End == Connector)
			return ForceBeam + ForceGravity / 2.f;
	}
	
	return FVector::ZeroVector;
}

void APBeam::BeginPlay()
{
	Super::BeginPlay();
	Length0 = FVector::Distance(Start->GetActorLocation(), End->GetActorLocation());
	if (Start != nullptr && End != nullptr)
	{
		Start->Beams.Add(this);
		End->Beams.Add(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Beam is not connected: %s"), *GetName());
	}
}

void APBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Start != nullptr && End != nullptr)
	{
		const FVector Direction = End->GetActorLocation() - Start->GetActorLocation();
		const FVector NewPos = Direction / 2 + Start->GetActorLocation();
		SetActorLocationAndRotation(NewPos, Direction.ToOrientationRotator());
	}
}

void APBeam::Break(APConnector* Connector)
{
	Connector->Disconnect(this);
	if (Connector == Start)
		Start = nullptr;
	else if (Connector == End)
		End = nullptr;
}

void APBeam::BreakAll()
{
	if (Start != nullptr && End != nullptr)
	{
		Start->Disconnect(this);
		End->Disconnect(this);
		Destroy();
	}
}

