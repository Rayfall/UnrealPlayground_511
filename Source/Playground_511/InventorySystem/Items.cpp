// Fill out your copyright notice in the Description page of Project Settings.


#include "Items.h"

UItems::UItems()
{
	Weight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void UItems::Use(APlayground_511Character* Character)
{

}
