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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bridge")
	TObjectPtr<APConnector> Start;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bridge")
	TObjectPtr<APConnector> End;

	UPROPERTY(EditAnywhere, Category = "Bridge")
	float Length0 = 100.f;
	UPROPERTY(EditAnywhere, Category = "Bridge")
	float Stiffness = 100.f;

	UPROPERTY(EditAnywhere, Category = "Bridge")
	float ForceBeamMax = 100.f;

	float ForceFactor = 0.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bridge, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

public:
	APBeam();

	FVector GetForceAtConnector(APConnector* Connector);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void Break(APConnector* Connector);
	void BreakAll();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnForceApplied(float Factor);
};
