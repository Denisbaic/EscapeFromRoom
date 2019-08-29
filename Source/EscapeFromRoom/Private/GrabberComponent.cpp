// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetItemByRayCast(300.f);
	// ...
}

AActor * UGrabberComponent::GetItemByRayCast(float RayLength) const
{
	FHitResult HitResult;
	
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);

	const FVector EndLocation = PlayerViewLocation + PlayerViewRotation.Vector()*RayLength;

	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true,GetOwner());
	
	//(GetWorld(), PlayerViewLocation, EndLocation, FColor::Red, false, GetWorld()->DeltaTimeSeconds, 0, 10);
	if(GetWorld()->LineTraceSingleByObjectType(HitResult, PlayerViewLocation, EndLocation, FCollisionObjectQueryParams(ECC_WorldDynamic),TraceParams))
	{
		//UE_LOG(LogTemp, Warning, TEXT("grabbed %s"), *HitResult.Actor->GetName());
		return HitResult.Actor.Get();
	}
	return nullptr;
}

