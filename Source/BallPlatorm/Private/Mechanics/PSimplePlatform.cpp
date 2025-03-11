// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/PSimplePlatform.h"


APSimplePlatform::APSimplePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	StartPoint = CreateDefaultSubobject<USceneComponent>("StartPoint");
	StartPoint->SetupAttachment(RootComponent);
	EndPoint = CreateDefaultSubobject<USceneComponent>("EndPoint");
	EndPoint->SetupAttachment(RootComponent);

	PlatformAttachmentPoint = CreateDefaultSubobject<USceneComponent>("PlatformAttachment");
	PlatformAttachmentPoint->SetupAttachment(RootComponent);
}

void APSimplePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MoveDirection == EPlatformDirection::Stop)
			return;

	CalculatePosition(MoveDirection == EPlatformDirection::Forward);
	MovePlatform();
}

void APSimplePlatform::SetNewPosition(const float Position)
{
	NewPosition = FMath::Lerp(StartPoint->GetComponentLocation(), EndPoint->GetComponentLocation(), Position);
}

void APSimplePlatform::CalculatePosition(const bool Opening)
{
	const FVector MoveDir = (EndPoint->GetComponentLocation() - StartPoint->GetComponentLocation()).GetSafeNormal();
	const float MoveDistance = Speed * GetWorld()->GetDeltaSeconds();
	FVector Position = PlatformAttachmentPoint->GetComponentLocation();
	
	if (Opening)
	{
		Position += MoveDir * MoveDistance;
		if (DistanceToGoal() <= MoveDistance)
		{
			Position = EndPoint->GetComponentLocation();
			Stop();
		}
	}
	else
	{
		Position -= MoveDir * MoveDistance;
		if (DistanceToStart() <= MoveDistance)
		{
			Position = StartPoint->GetComponentLocation();
			Stop();
		}
	}

	NewPosition = Position;
}

void APSimplePlatform::MovePlatform() const
{
	PlatformAttachmentPoint->SetWorldLocation(NewPosition);
}

USceneComponent* APSimplePlatform::GetDefaultAttachComponent() const
{
	return PlatformAttachmentPoint;
}

#if WITH_EDITOR
void APSimplePlatform::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	SetNewPosition(StartPosition);
	MovePlatform();
}
#endif

