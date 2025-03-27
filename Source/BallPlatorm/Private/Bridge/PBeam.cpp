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
			FLinearColor Color = UKismetMathLibrary::LinearColorLerp(FLinearColor::Green, FLinearColor::Red, ForceFactor);
			DrawDebugLine(GetWorld(), StartPos, EndPos, FColor(Color.R, Color.G, Color.B));
			if (ForceFactor >= 1.0f)
			{
				// Break(Connector);
			}
		}

		// FString Results = FString::Printf(TEXT("Force: %s"), *ForceBeam.ToString());
		// UKismetSystemLibrary::PrintString(GetWorld(), Results, true, false, FLinearColor::Blue, 2., FName(*GetName()));
		FString Results = FString::Printf(TEXT("Length0: %f vs Current: %f"), Length0, Length.Size());
		UKismetSystemLibrary::PrintString(GetWorld(), Results, true, false, FLinearColor::Blue, 2., FName(*GetName()));

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
	Start->Beams.Add(this);
	End->Beams.Add(this);
}

void APBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APBeam::Break(APConnector* Connector)
{
	Connector->Disconnect(this);
	if (Connector == Start)
		Start = nullptr;
	else if (Connector == End)
		End = nullptr;
}

