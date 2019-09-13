// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckTriggerOnMassComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"


void UCheckTriggerOnMassComponent::BeginPlay()
{
	Super::BeginPlay();
}

float UCheckTriggerOnMassComponent::GetTotalMassOfActorsOnPlate() const
{
	if (!TriggerVolume)
		return 0.f;

	TArray<AActor*> OverlappingActors;
	float TotalMass = 0.f;

	TriggerVolume->GetOverlappingActors(OverlappingActors);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	TriggerVolume->GetOverlappingComponents(OverlappingComponents);

	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UCheckTriggerOnMassComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		DoorOpenEvent.Broadcast();
	}
	else
	{
		DoorCloseEvent.Broadcast();
	}
}
