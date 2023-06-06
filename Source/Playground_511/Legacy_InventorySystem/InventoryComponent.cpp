// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "ItemActor.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    Capacity = 20;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    for (auto& Item : DefaultItems)
    {
        AddItem(Item);
    }
}

bool UInventoryComponent::AddItem(AItemActor* Item)
{
    if (Items.Num() >= Capacity || !Item)
    {
        return false;
    }

    Item->OwningInventory = this;
    //Item->World = GetWorld();
    Items.Add(Item);

    //Update UI
    OnInventoryUpdated.Broadcast();

    return true;
}

bool UInventoryComponent::RemoveItem(AItemActor* Item)
{
    if (Item)
    {
        Item->OwningInventory = nullptr;
        //Item->World = nullptr;
        Items.RemoveSingle(Item);
        OnInventoryUpdated.Broadcast();
        return true;
    }
    return false;
}