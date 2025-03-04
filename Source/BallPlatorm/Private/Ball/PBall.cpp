// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/PBall.h"

#include "Ball/PBallMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"


APBall::APBall()
{
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = BallMesh;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void APBall::BeginPlay()
{
	Super::BeginPlay();
	
}

void APBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APBall::Jump() const
{
	MovementComponent->Jump();
}

void APBall::Move(const FVector MoveInput)
{
	MovementComponent->Move(MoveInput);
}

