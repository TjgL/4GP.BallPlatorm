// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PRotatingLever.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class BALLPLATORM_API APRotatingLever : public AActor
{
	GENERATED_BODY()

public:
	APRotatingLever();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetRotationPercentage() const { return RotationDone / Limits; }

private:
	void CheckRotationProgress();

private: // Settings
	UPROPERTY(EditAnywhere, Category = Platformer, meta = (AllowPrivateAccess = true))
	float RotationDone = 0.f;

	UPROPERTY(EditAnywhere, Category = Platformer, meta = (AllowPrivateAccess = true))
	FRotator PreviousRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category = Platformer, meta = (AllowPrivateAccess = true, UIMin = 0))
	float Limits = 360.f;

private: // Components
	UPROPERTY(EditAnywhere, Category = Platformer, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMeshComponent> CenterMesh;

	UPROPERTY(EditAnywhere, Category = Platformer, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMeshComponent> RotatingMesh;

	UPROPERTY(EditAnywhere, Category = Platformer, meta = (AllowPrivateAccess = true))
	TObjectPtr<UPhysicsConstraintComponent> Constraint;
};
