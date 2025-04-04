﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/PSplinePlatform.h"

#include "Components/SplineComponent.h"


APSplinePlatform::APSplinePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineComponent->SetupAttachment(RootComponent);

	PlatformAttachmentPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PlatformAttachment"));
	PlatformAttachmentPoint->SetupAttachment(SplineComponent);
}

void APSplinePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MoveDirection == EPlatformDirection::Stop)
		return;

	CalculatePosition(MoveDirection == EPlatformDirection::Forward);
	MovePlatform();
}

void APSplinePlatform::CalculatePosition(const bool Opening)
{
	float const SplineLenght = SplineComponent->GetSplineLength();
	float const Distance = MoveSpeed * GetWorld()->GetDeltaSeconds();
	bool const IsLoop = SplineComponent->IsClosedLoop();
	
	float NewPosition = PositionOnSpline + (Opening ? 1 : -1) * ((Distance / SplineLenght) * 100);
	
	if (NewPosition > 1.f)
	{
		if (IsLoop)
		{
			NewPosition = NewPosition - 1.f;
		}
		else
		{
			MoveDirection = bDoReverseOnEnd ? EPlatformDirection::Back : EPlatformDirection::Stop;
			NewPosition = PositionOnSpline - (Distance / SplineLenght) * 100;	
		}
	}
	else if (NewPosition < 0.f)
	{
		if (IsLoop)
		{
			NewPosition = NewPosition + 1.f;
		}
		else
		{
			MoveDirection = bDoReverseOnEnd ? EPlatformDirection::Forward : EPlatformDirection::Stop;
			NewPosition = PositionOnSpline + (Distance / SplineLenght) * 100;
		}
	}
	
	PositionOnSpline = NewPosition;
}

void APSplinePlatform::MovePlatform() const
{
	FVector const PlatformPosition = SplineComponent->GetLocationAtTime(PositionOnSpline, ESplineCoordinateSpace::World);
	FQuat const RailRotation = SplineComponent->GetQuaternionAtTime(PositionOnSpline, ESplineCoordinateSpace::World);

	if (bLockRotationToSpline)
	{
		PlatformAttachmentPoint->SetWorldLocationAndRotation(PlatformPosition, RailRotation);
	}
	else
	{
		PlatformAttachmentPoint->SetWorldLocation(PlatformPosition);
	}
}

USceneComponent* APSplinePlatform::GetDefaultAttachComponent() const
{
	return PlatformAttachmentPoint;
}

#if WITH_EDITOR
void APSplinePlatform::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	MovePlatform();
}
#endif

