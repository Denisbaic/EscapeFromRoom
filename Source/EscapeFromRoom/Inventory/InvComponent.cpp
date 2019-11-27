// Fill out your copyright notice in the Description page of Project Settings.


#include "InvComponent.h"
#include "Player/EscapeFromRoomPlayerController.h"
#include "Components/SphereComponent.h"
#include "AutoPickup.h"
#include "Inventory/Interactable.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UInvComponent::UInvComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInvComponent::BeginPlay()
{
	Super::BeginPlay();
	if(ensure(CollectionSphere))
		UE_LOG(LogTemp,Error,TEXT("isn't set the collection sphere in begin play"))
}

void UInvComponent::CollectAutoPickups()
{
	// Get all overlapping Actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);
	
	AEscapeFromRoomPlayerController* PlayerController = Cast<AEscapeFromRoomPlayerController>(Cast<ACharacter>(GetOwner()));
	
	// For each collected Actor
	for (const auto& ActorCollected : CollectedActors)
	{
		// Cast the actor to AAutoPickup
		AAutoPickup* const TestPickup = Cast<AAutoPickup>(ActorCollected);
		// If the cast is successful and the pickup is valid and active 
		if (TestPickup && !TestPickup->IsPendingKill())
		{
			TestPickup->Collect(PlayerController);
		}
	}
}

void UInvComponent::CheckForInteractables()
{
	// Create a LineTrace to check for a hit
	FHitResult HitResult;

	int32 Range = 500;

	FVector StartTrace;

	FRotator PlayerViewRotation;
	//Setting PlayerViewLocation and PlayerViewRotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(StartTrace, PlayerViewRotation);


	FVector EndTrace = (PlayerViewRotation.Vector() * Range) + StartTrace;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());


	AEscapeFromRoomPlayerController* PlayerController = Cast<AEscapeFromRoomPlayerController>(Cast<ACharacter>(GetOwner())->GetController());

	if (PlayerController)
	{
		// Check if something is hit
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			// Cast the actor to AInteractable
			AInteractable* Interactable = Cast<AInteractable>(HitResult.GetActor());
			// If the cast is successful
			if (Interactable)
			{
				PlayerController->CurrentInteractable = Interactable;
				return;
			}
		}

		PlayerController->CurrentInteractable = nullptr;
	}
}


// Called every frame
void UInvComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CollectAutoPickups();
	CheckForInteractables();
}

