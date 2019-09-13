// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorRiddles/OpenDoorComponent.h"
#include "CheckTriggerOnMassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEFROMROOM_API UCheckTriggerOnMassComponent : public UOpenDoorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		ATriggerVolume* TriggerVolume;

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
