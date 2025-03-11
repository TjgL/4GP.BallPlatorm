// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PEPlatformDirection.h"
#include "GameFramework/Actor.h"
#include "PSplinePlatform.generated.h"

class USplineComponent;

UCLASS()
class BALLPLATORM_API APSplinePlatform : public AActor
{
	GENERATED_BODY()

public:
	APSplinePlatform();
	virtual void Tick(float DeltaTime) override;
	void CalculatePosition(bool Opening);
	void MovePlatform() const;
	
	virtual USceneComponent* GetDefaultAttachComponent() const override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	/* The Position of the platform on the spline. */
	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true, ClampMin = 0.f, ClampMax = 1.f))
	float PositionOnSpline = 0.f;

	/* If set, the rotation of the platform will match the angle of the spline. */
	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true))
	bool bLockRotationToSpline = true;

	/* The direction of the platform movement. */
	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true))
	EPlatformDirection MoveDirection;

	/* The speed at which the platform moves. */
	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true, ClampMin = 0.f))
	float MoveSpeed = 2.f;

	/* If set, the platform will revert if it reaches the end of a non-closed spline. */
	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true))
	bool bDoReverseOnEnd = true;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> PlatformAttachmentPoint;
};
