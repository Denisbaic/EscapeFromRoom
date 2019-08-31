// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabberComponent.generated.h"

class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEFROMROOM_API UGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void SetupInputComponent();
	// Sets default values for this component's properties
	UGrabberComponent();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float RayLength = 100.f;

	UPhysicsHandleComponent* PhysicsHandle;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void FindPhysicsHandleComponent();
	FVector GetReachLineStart() const;
	FVector GetReachLineEnd() const;
	FHitResult GetItemByRayCast() const;

	void Grab();
	void Release();
};
