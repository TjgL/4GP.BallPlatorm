// Fill out your copyright notice in the Description page of Project Settings.


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

void APSplinePlatform::BeginPlay()
{
	Super::BeginPlay();
	
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
	float const NewPosition = PositionOnSpline + (Opening ? 1 : -1) * ((Distance / SplineLenght) * 100);
	
	if (Opening)
	{
		if (NewPosition > 1.f)
		{
			MoveDirection = bDoReverseOnEnd ? EPlatformDirection::Back : EPlatformDirection::Stop;
			PositionOnSpline = PositionOnSpline - (Distance / SplineLenght) * 100;
			return;
		}
	}
	else
	{
		if (NewPosition < 0.f)
		{
			MoveDirection = bDoReverseOnEnd ? EPlatformDirection::Forward : EPlatformDirection::Stop;
			PositionOnSpline = PositionOnSpline + (Distance / SplineLenght) * 100;
			return;
		}
	}
	
	PositionOnSpline = NewPosition;
}

void APSplinePlatform::MovePlatform() const
{
	float const SplineLenght = SplineComponent->GetSplineLength();
	FVector const PlatformPosition = SplineComponent->GetLocationAtDistanceAlongSpline(PositionOnSpline * SplineLenght, ESplineCoordinateSpace::World);
	FQuat const RailRotation = SplineComponent->GetQuaternionAtDistanceAlongSpline(PositionOnSpline * SplineLenght, ESplineCoordinateSpace::World);

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

