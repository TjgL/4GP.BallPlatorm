// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PBallMovementComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BALLPLATORM_API UPBallMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPBallMovementComponent();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	UFUNCTION(BlueprintCallable)
	void Initialize(UPrimitiveComponent* BallCollision);
	
	UFUNCTION(BlueprintCallable)
	void Jump();
	
	UFUNCTION(BlueprintCallable)
	void Move(FVector2D MoveDirection);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess=true))
	int MaxJumpCount = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess=true))
	float JumpSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess=true))
	float MoveSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess=true))
	float ForceMultiplier = 100.f;
	
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess=true))
	int CurrentJumpCount = MaxJumpCount;
};
