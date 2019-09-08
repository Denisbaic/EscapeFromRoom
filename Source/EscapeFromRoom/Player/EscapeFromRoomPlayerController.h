// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inventory/Interactable.h"
#include "Engine/DataTable.h"
#include "Inventory/InvItem.h"
#include "EscapeFromRoomPlayerController.generated.h"


UCLASS()
class ESCAPEFROMROOM_API AEscapeFromRoomPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AEscapeFromRoomPlayerController();

	UFUNCTION(BlueprintImplementableEvent)
		void ReloadInventory();

	UFUNCTION(BlueprintCallable, Category = "Utils")
		int32 GetInventoryWeight();

	UFUNCTION(BlueprintCallable, Category = "Utils")
		bool AddItemToInventoryByID(FName ID);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class AInteractable* CurrentInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FInvItem> Inventory;

	//additional functionality
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		//int32 Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 InventorySlotLimit;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 InventoryWeightLimit;

protected:
	void Interact();

	virtual void SetupInputComponent() override;
};
