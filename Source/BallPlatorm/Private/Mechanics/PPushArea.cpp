// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/PPushArea.h"

#include "Kismet/KismetSystemLibrary.h"

UPPushArea::UPPushArea()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPPushArea::BeginPlay()
{
	Super::BeginPlay();
	
	OnComponentBeginOverlap.AddUniqueDynamic(this, &UPPushArea::OnOverlap);
	OnComponentEndOverlap.AddUniqueDynamic(this, &UPPushArea::OnEndOverlap);
}

void UPPushArea::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UMeshComponent* MeshComponent = Cast<UMeshComponent>(OtherComp))
		ObjectsToPush.AddUnique(MeshComponent);
}

void UPPushArea::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UMeshComponent* MeshComponent = Cast<UMeshComponent>(OtherComp))
		ObjectsToPush.Remove(MeshComponent);
}


void UPPushArea::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugVisualizers();

	if (ObjectsToPush.Num() <= 0)
		return;

	PushObjects(DeltaTime);
}

void UPPushArea::DrawDebugVisualizers() const
{
	const FVector Location = GetComponentLocation();
	UKismetSystemLibrary::DrawDebugBox(GetWorld(), Location, BoxExtent, FColor::Blue, GetComponentRotation(), 0.1f, 1.f); 
	// DrawDebugBox(GetWorld(), Location, BoxExtent, FColor::Blue, false, 0.1f, 1.f);
	DrawDebugDirectionalArrow(GetWorld(), Location, GetForwardVector() * BoxExtent.Size() + Location, 100.f, FColor::Blue, false, 0.1f, 0, 1.f);
}

void UPPushArea::PushObjects(float DeltaTime)
{
	const FVector Force = GetComponentRotation().Vector() * PushForce;
	
	for (const auto Object : ObjectsToPush)
	{
		Object->AddForce(Force);
	}
}


