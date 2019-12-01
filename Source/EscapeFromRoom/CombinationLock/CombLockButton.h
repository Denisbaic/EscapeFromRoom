// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ManClick.h"
#include "CombLockButton.generated.h"

UENUM()
enum class EButtonFunction : uint8
{
	AddText,
	DeleteLast,
	DeleteAll,
	Compare
};

class ACombLock;
UCLASS()
class ESCAPEFROMROOM_API ACombLockButton : public AManClick
{
	GENERATED_BODY()
	
public:
	ACombLockButton();
	EButtonFunction ButtonFunction;
	UPROPERTY(EditAnywhere)
		FString CodeContained;
	void Interact_Implementation(APlayerController* Controller) override;
};
