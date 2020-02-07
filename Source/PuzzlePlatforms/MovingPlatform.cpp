// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartLocation = GetActorLocation();
	EndLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority())
		return;

	if (ActiveTriggers < 1)
		return;

	FVector Target;

	FVector CurrentLocation = GetActorLocation();
	FVector Direction = EndLocation - StartLocation;
	
	Direction.Normalize();
	CurrentLocation += Direction * Speed*DeltaTime;
	SetActorLocation(CurrentLocation);

	if ((CurrentLocation - StartLocation).Size() > (EndLocation - StartLocation).Size()) {
		FVector tmp = EndLocation;
		EndLocation = StartLocation;
		StartLocation = tmp;
	}

}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
		ActiveTriggers--;
}
