// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/PRotatingLever.h"

#include "Kismet/KismetMathLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


APRotatingLever::APRotatingLever()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	const FName CenterMeshName = FName(TEXT("Center Mesh"));
	CenterMesh = CreateDefaultSubobject<UStaticMeshComponent>(CenterMeshName);
	CenterMesh->SetupAttachment(RootComponent);

	const FName RotatingMeshName = FName(TEXT("Rotating Mesh"));
	RotatingMesh = CreateDefaultSubobject<UStaticMeshComponent>(RotatingMeshName);
	RotatingMesh->SetupAttachment(RootComponent);

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint"));
	Constraint->SetupAttachment(RootComponent);
	Constraint->ComponentName1 = FConstrainComponentPropName(CenterMeshName);
	Constraint->ComponentName2 = FConstrainComponentPropName(RotatingMeshName);
}

void APRotatingLever::BeginPlay()
{
	Super::BeginPlay();
	PreviousRotation = RotatingMesh->GetComponentRotation();
}

void APRotatingLever::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckRotationProgress();
}

void APRotatingLever::CheckRotationProgress()
{
	const FRotator CurrentRotation = RotatingMesh->GetComponentRotation();
	const float RotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(CurrentRotation, PreviousRotation).Yaw;

	RotationDone += RotationDelta;
	PreviousRotation = CurrentRotation;

	if (RotationDone <= 0 || RotationDone >= Limits)
	{
		Constraint->SetAngularSwing1Limit(ACM_Limited, 0);
	}
	else
	{
		Constraint->SetAngularSwing1Limit(ACM_Free, 0);
	}
}

