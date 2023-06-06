// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItemActor.h"
#include "InventoryComponent.h"
#include "../Playground_511Character.h"

void AFoodItemActor::Use(APlayground_511Character* Character)
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
