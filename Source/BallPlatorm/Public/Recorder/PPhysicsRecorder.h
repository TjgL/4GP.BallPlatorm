// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PRecorderData.h"
#include "PRecorderStates.h"
#include "Components/ActorComponent.h"
#include "PPhysicsRecorder.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BALLPLATORM_API UPPhysicsRecorder : public UActorComponent
{
	GENERATED_BODY()

public:
	UPPhysicsRecorder();
	// Voir pour register une tick function custom, au niveau du component, bind plusieurs ticks fonction
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void RecordOneFrame();
	void RewindLastFrame();
	void SetMeshToData(const FPRecorderData& Data) const;
	void SetRecordState(const ERecordState State) { RecordState = State; }

	void CheckQueueSize();

	UFUNCTION(BlueprintCallable)
	void Setup(UMeshComponent* MeshToRecord);


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Recorder, meta = (AllowPrivateAccess = true, ClampMin = 0))
	ERecordState RecordState = ERecordState::ERS_Recording;
	
	UPROPERTY(EditAnywhere, Category = Recorder, meta = (AllowPrivateAccess = true, ClampMin = 0))
	int MaxRecordedFrame = 240;
	
	UPROPERTY()
	TObjectPtr<UMeshComponent> Mesh;
	
	TArray<FPRecorderData*> RecordedStates = TArray<FPRecorderData*>();
	int CurrentIndex = 0;
};
