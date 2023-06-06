// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    UseActionText = FText::FromString("Use");
    ItemDisplayName = FText::FromString("Item");
    ItemDescription = FText::FromString("Description");
    Weight = 1.f;

}

void AItemActor::BeginPlay()
{
    Super::BeginPlay();
}

void AItemActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AItemActor::Use(APlayground_511Character* Character)
{

}