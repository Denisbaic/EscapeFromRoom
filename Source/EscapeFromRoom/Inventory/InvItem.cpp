#include "InvItem.h"

FInvItem::FInvItem(): Name(FText::FromString("No Name")),Weight(1),Value(1),Thumbnail(nullptr), Description(FText::FromString("No Description"))
{}

bool FInvItem::operator==(const FInvItem& OtherItem) const
{
	if (ItemID == OtherItem.ItemID)
		return true;
	return false;
}

