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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bridge, meta = (AllowPrivateAccess))
	TArray<TObjectPtr<APBeam>> Beams = TArray<TObjectPtr<APBeam>>();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bridge")
	bool bIsAnchor = false;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bridge, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
public:
	APConnector();

	FVector ForceSumStored;
	float MassSumStored;

	void CalculateForces();
	void Disconnect(APBeam* APBeam);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
