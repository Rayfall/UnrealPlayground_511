// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReubInventoryComponent.generated.h"

//Blueprints will bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYGROUND_511_API UReubInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReubInventoryComponent();

    // Called when the game starts
    virtual void BeginPlay() override;

    bool AddItem(class UItems* Item);
    bool RemoveItem(class UItems* Item);

    UPROPERTY(EditDefaultsOnly, Instanced)
    TArray<class UItems*> DefaultItems;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 Capacity;

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnInventoryUpdated OnInventoryUpdated;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
    TArray<class UItems*> Items;
};
