// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoorComponent.h"
#include "CheckPlayerInvDoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEFROMROOM_API UCheckPlayerInvDoorComponent : public UOpenDoorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCheckPlayerInvDoorComponent();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FName ItemId;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		ATriggerVolume* TriggerVolume;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void CheckInventory(AActor* OverlappedActor, AActor* OtherActor);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
