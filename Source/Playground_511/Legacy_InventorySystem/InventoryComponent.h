// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

//Blueprints will bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYGROUND_511_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

    bool AddItem(class AItemActor* Item);
    bool RemoveItem(class AItemActor* Item);

    UPROPERTY(EditDefaultsOnly, Instanced)
    TArray<class AItemActor*> DefaultItems;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 Capacity;

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnInventoryUpdate OnInventoryUpdated;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
    TArray<class AItemActor*> Items;
};
