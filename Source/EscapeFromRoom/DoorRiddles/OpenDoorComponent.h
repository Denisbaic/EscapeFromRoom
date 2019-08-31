// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoorComponent.generated.h"

class ATriggerVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEFROMROOM_API UOpenDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorComponent();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		ATriggerVolume* TriggerVolume;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent DoorOpenEvent;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent DoorCloseEvent;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 100.f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	float GetTotalMassOfActorsOnPlate() const;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
