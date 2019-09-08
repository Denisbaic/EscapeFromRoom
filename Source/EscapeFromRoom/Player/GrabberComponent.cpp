// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}
void UGrabberComponent::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
}
void UGrabberComponent::SetupInputComponent()
{
	if(GetOwner()->InputComponent)
	{
		GetOwner()->InputComponent->BindAction("GetItem", IE_Pressed, this, &UGrabberComponent::Grab);
		GetOwner()->InputComponent->BindAction("GetItem", IE_Released, this, &UGrabberComponent::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}


FVector UGrabberComponent::GetReachLineStart() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector UGrabberComponent::GetReachLineEnd() const
{
	FVector  PlayerViewLocation;
	FRotator PlayerViewRotation;
	//Setting PlayerViewLocation and PlayerViewRotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);

	return  PlayerViewLocation + PlayerViewRotation.Vector()*RayLength;
}

FHitResult UGrabberComponent::GetItemByRayCast() const
{
	FHitResult HitResult;

	const FVector EndLocation = GetReachLineEnd();

	const FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true,GetOwner());

	GetWorld()->LineTraceSingleByObjectType(HitResult, GetReachLineStart(), EndLocation, FCollisionObjectQueryParams(ECC_PhysicsBody), TraceParams);


	
	return HitResult;
}

void UGrabberComponent::Grab()
{
	const FHitResult HitResult = GetItemByRayCast();
	const auto ActorHit = HitResult.Actor;

	if(!ActorHit.Get())
		return;

	const auto ComponentUnderHit = HitResult.Component.Get();

	PhysicsHandle->GrabComponent(ComponentUnderHit, NAME_None, ComponentUnderHit->GetOwner()->GetActorLocation(), true);

}

void UGrabberComponent::Release()
{
	PhysicsHandle->ReleaseComponent();
}
