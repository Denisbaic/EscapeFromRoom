// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DefaultPawn.h"
#include "PlayerPawn.generated.h"

class UGrabberComponent;

UCLASS()
class ESCAPEFROMROOM_API APlayerPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	/** Collection sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollectionSphere;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UPhysicsHandleComponent* HandleComponent;

		/** Function to collect every AutoPickup in range. */
	void CollectAutoPickups();

	/** Function to check for the closest Interactable in sight and in range. */
	void CheckForInteractables();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
