// Fill out your copyright notice in the Description page of Project Settings.


#include "ReubInventoryComponent.h"
#include "Items.h"

// Sets default values for this component's properties
UReubInventoryComponent::UReubInventoryComponent()
{
	Capacity = 20;
}

void UReubInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UReubInventoryComponent::AddItem(UItems* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	//Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UReubInventoryComponent::RemoveItem(UItems* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}