// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PBeam.generated.h"

class APConnector;

UCLASS()
class BALLPLATORM_API APBeam : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Bridge")
	TObjectPtr<APConnector> Start;
	UPROPERTY(EditAnywhere, Category = "Bridge")
	TObjectPtr<APConnector> End;

	UPROPERTY(EditAnywhere, Category = "Bridge")
	float Length0 = 100.f;
	UPROPERTY(EditAnywhere, Category = "Bridge")
	float Stiffness = 100.f;

	UPROPERTY(EditAnywhere, Category = "Bridge")
	float ForceBeamMax = 100.f;

	float ForceFactor = 0.f;

public:
	APBeam();

	FVector2D GetForceAtConnector(APConnector* Connector);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
