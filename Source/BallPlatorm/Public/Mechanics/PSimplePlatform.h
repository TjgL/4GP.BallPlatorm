// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PEPlatformDirection.h"
#include "GameFramework/Actor.h"
#include "PSimplePlatform.generated.h"

UCLASS()
class BALLPLATORM_API APSimplePlatform : public AActor
{
	GENERATED_BODY()

public:
	APSimplePlatform();
	virtual void Tick(float DeltaTime) override;
	void CalculatePosition(bool Opening);

	UFUNCTION(BlueprintCallable)
	void MovePlatform() const;
	
	UFUNCTION(BlueprintCallable)
	void SetNewPosition(float Position);
	
	virtual USceneComponent* GetDefaultAttachComponent() const override;

public:
	float DistanceToGoal() const { return FVector::Distance(PlatformAttachmentPoint->GetComponentLocation(), EndPoint->GetComponentLocation()); } 
	float DistanceToStart() const { return FVector::Distance(PlatformAttachmentPoint->GetComponentLocation(), StartPoint->GetComponentLocation()); } 

	void Stop() { MoveDirection = EPlatformDirection::Stop; }
	
private:
	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true))
	EPlatformDirection MoveDirection;

	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true, ClampMin=0, ClampMax=1))
	float StartPosition = 0.f;

	UPROPERTY(EditAnywhere, Category=Platform, meta = (AllowPrivateAccess = true))
	float Speed = 100.f;

	FVector NewPosition;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> EndPoint;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> StartPoint;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> PlatformAttachmentPoint;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif
};
