// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/PBallMovementComponent.h"


UPBallMovementComponent::UPBallMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPBallMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UPBallMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

