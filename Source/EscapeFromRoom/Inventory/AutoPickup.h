// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutoPickup.generated.h"

UCLASS()
class ESCAPEFROMROOM_API AAutoPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	AAutoPickup();

	UFUNCTION(BlueprintNativeEvent)
		void Collect(APlayerController* Controller);
	virtual void Collect_Implementation(APlayerController* Controller);

	FName GetItemID();

protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;
};
