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

void UPPhysicsRecorder::InitializeComponent()
{
	Super::InitializeComponent();

	
}

void UPPhysicsRecorder::CheckQueueSize()
{
	if (CurrentIndex >= MaxRecordedFrame)
	{
		CurrentIndex = 0;
	}
	else if (CurrentIndex < 0)
	{
		if (RecordedStates[MaxRecordedFrame] == nullptr)
		{
			CurrentIndex = 0;
		}
		else
		{
			CurrentIndex = MaxRecordedFrame;
		}
	}
}

void UPPhysicsRecorder::Setup(UMeshComponent* MeshToRecord)
{
	Mesh = MeshToRecord;
}

void UPPhysicsRecorder::RecordOneFrame()
{
	FPRecorderData Data = FPRecorderData(Mesh->GetPhysicsLinearVelocity(),
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
		return;
	
	SetMeshToData(*Data);
	CurrentIndex--;
	CheckQueueSize();
}

void UPPhysicsRecorder::SetMeshToData(const FPRecorderData& Data)
{
	Mesh->SetPhysicsLinearVelocity(Data.Velocity);
	Mesh->SetPhysicsAngularVelocityInRadians(Data.AngularVelocityRadians);
	Mesh->SetWorldLocationAndRotation(Data.Position, Data.Rotation);
}


