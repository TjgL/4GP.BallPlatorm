// Fill out your copyright notice in the Description page of Project Settings.


#include "Recorder/PPhysicsRecorder.h"


UPPhysicsRecorder::UPPhysicsRecorder()
{
	PrimaryComponentTick.bCanEverTick = true;
	RecordedStates.Init(nullptr, MaxRecordedFrame);
}


void UPPhysicsRecorder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (RecordState)
	{
	case ERecordState::ERS_Stopped:
		break;
		
	case ERecordState::ERS_Recording:
		RecordOneFrame();
		break;
		
	case ERecordState::ERS_Rewinding:
		RewindLastFrame();
		break;
		
	default: ;
		UE_LOG(LogTemp, Fatal, TEXT("This should never happen."))
	}
}

void UPPhysicsRecorder::CheckQueueSize()
{
	// Since our array is limited in size, we go back to the first position to add new data, overriding the previous n-MaxRecordedFrame physic data
	if (CurrentIndex >= MaxRecordedFrame)
	{
		CurrentIndex = 0;
	}
	else if (CurrentIndex < 0)
	{
		if (RecordedStates[MaxRecordedFrame - 1] == nullptr)
		{
			CurrentIndex = 0;
			RecordState = ERecordState::ERS_Recording;
		}
		else
		{
			CurrentIndex = MaxRecordedFrame - 1;
		}
	}
}

void UPPhysicsRecorder::Setup(UMeshComponent* MeshToRecord)
{
	Mesh = MeshToRecord;
}

void UPPhysicsRecorder::RecordOneFrame()
{
	FPRecorderData* Data = new FPRecorderData(Mesh->GetPhysicsLinearVelocity(),
		Mesh->GetPhysicsAngularVelocityInRadians(),
		Mesh->GetComponentLocation(),
		Mesh->GetComponentRotation());

	RecordedStates[CurrentIndex] = Data;
	CurrentIndex++;
	CheckQueueSize();
}

void UPPhysicsRecorder::RewindLastFrame()
{
	const FPRecorderData* Data = RecordedStates[CurrentIndex];
	if (Data == nullptr)
	{
		CurrentIndex = 0;
		RecordState = ERecordState::ERS_Recording;
		return;
	}
	
	SetMeshToData(*Data);
	RecordedStates[CurrentIndex] = nullptr;
	CurrentIndex--;
	CheckQueueSize();
}

void UPPhysicsRecorder::SetMeshToData(const FPRecorderData& Data) const
{
	Mesh->SetPhysicsLinearVelocity(Data.Velocity);
	Mesh->SetPhysicsAngularVelocityInRadians(Data.AngularVelocityRadians);
	Mesh->SetWorldLocationAndRotation(Data.Position, Data.Rotation);
}


