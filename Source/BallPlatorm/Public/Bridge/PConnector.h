// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PConnector.generated.h"

class APBeam;

UCLASS()
class BALLPLATORM_API APConnector : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess))
	TArray<TObjectPtr<APBeam>> Beams = TArray<TObjectPtr<APBeam>>();
	
	UPROPERTY(EditAnywhere, Category = "Bridge")
	bool bIsAnchor = false;
	
public:
	APConnector();

	FVector2D ForceSumStored;
	float MassSumStored;

	void CalculateForces();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
