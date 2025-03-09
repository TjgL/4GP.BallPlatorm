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

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true, ClampMin = 0.f, ClampMax = 1.f))
	float PositionOnSpline = 0.f;

	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true))
	bool bLockRotationToSpline = true;

	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true))
	EPlatformDirection MoveDirection;

	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true, ClampMin = 0.f))
	float MoveSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true))
	bool bDoReverseOnEnd = true;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> PlatformAttachmentPoint;
};
