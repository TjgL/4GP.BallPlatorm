// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/PBallMovementComponent.h"


UPBallMovementComponent::UPBallMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPBallMovementComponent::Initialize(UPrimitiveComponent* BallCollision)
{
	Mesh = BallCollision;
	Mesh->OnComponentHit.AddUniqueDynamic(this, &UPBallMovementComponent::OnHit);
}


void UPBallMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPBallMovementComponent::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	CurrentJumpCount = MaxJumpCount;
}

void UPBallMovementComponent::Jump()
{
	if (Mesh)
	{
		if (CurrentJumpCount <= 0)
			return;
		
		CurrentJumpCount--;
		Mesh->AddForce(FVector(0.0f, 0.0f, JumpSpeed * ForceMultiplier));
	}
}

void UPBallMovementComponent::Move(const FVector MoveDirection) const
{
	if (Mesh)
	{
		const FVector Speed = MoveDirection * MoveSpeed * ForceMultiplier;
		Mesh->AddForce(FVector(Speed.X, Speed.Y, 0.0f));
	}
}

