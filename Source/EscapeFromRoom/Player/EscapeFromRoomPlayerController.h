// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inventory/Interactable.h"
#include "Engine/DataTable.h"
#include "Inventory/InvItem.h"
#include "EscapeFromRoomPlayerController.generated.h"
/*
USTRUCT(BlueprintType)
struct FInvItem  : public FTableRowBase
{
	GENERATED_BODY()

	FInvItem(): Thumbnail(nullptr)
	{
		this->Name = FText::FromString("No Name");
		this->Weight = 1;
		this->Value = 1;
		this->Description = FText::FromString("No Description");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	bool operator==(const FInvItem& OtherItem) const
	{
		if (ItemID == OtherItem.ItemID)
			return true;
		return false;
	}
};
*/

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
