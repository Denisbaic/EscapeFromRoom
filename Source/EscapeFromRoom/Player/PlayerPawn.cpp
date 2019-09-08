// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Inventory/Interactable.h"
#include "Inventory/AutoPickup.h"
#include "EscapeFromRoomPlayerController.h"
#include "Components/SphereComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(FName("CollectionSphere"));
	CollectionSphere->SetupAttachment(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerPawn::CollectAutoPickups()
{
	// Get all overlapping Actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	AEscapeFromRoomPlayerController* PlayerController = Cast<AEscapeFromRoomPlayerController>(GetController());

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

void APlayerPawn::CheckForInteractables()
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
	QueryParams.AddIgnoredActor(this);


		AEscapeFromRoomPlayerController* PlayerController = Cast<AEscapeFromRoomPlayerController>(GetController());

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
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CollectAutoPickups();
	CheckForInteractables();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

