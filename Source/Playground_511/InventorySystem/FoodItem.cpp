// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"
#include "ReubInventoryComponent.h"
#include "Playground_511/Playground_511Character.h"

void UFoodItem::Use(APlayground_511Character* Character)
{
	if (Character) 
	{ 
		Character->Health += HealthToHeal; 

		if (OwningInventory)
		{
			OwningInventory->RemoveItem(this);
		}
	}

}
