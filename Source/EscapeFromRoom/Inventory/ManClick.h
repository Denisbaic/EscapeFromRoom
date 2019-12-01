// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Interactable.h"
#include "ManClick.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMROOM_API AManClick : public AInteractable
{
	GENERATED_BODY()
	
public:
	AManClick();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UStaticMeshComponent* ClickedMesh;

};
