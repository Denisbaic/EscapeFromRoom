// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

// Sets default values
FInventoryItem::FInventoryItem()
{
	this->Name = FText::FromString("No Name");
	this->Weight = 1;
	this->Value = 1;
	this->Description = FText::FromString("No Description");

}

bool FInventoryItem::operator==(const FInventoryItem& OtherItem) const
{
	if (ItemID == OtherItem.ItemID)
		return true;
	return false;
}