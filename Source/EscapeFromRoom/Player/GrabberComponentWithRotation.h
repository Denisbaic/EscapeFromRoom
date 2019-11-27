// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/GrabberComponent.h"
#include "GrabberComponentWithRotation.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEFROMROOM_API UGrabberComponentWithRotation : public UGrabberComponent
{
	GENERATED_BODY()


public:
	UGrabberComponentWithRotation();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "PlayerPawn")
		void RotationMode();
	void SetupInputComponent() override;

	void Release() override;
private:
	UPROPERTY()
		FRotator RotatorInBeginI;
	UPROPERTY()
		bool bRotationMode=false;
};
