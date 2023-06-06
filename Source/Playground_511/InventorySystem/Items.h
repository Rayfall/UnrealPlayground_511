// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class PLAYGROUND_511_API UItems : public UObject
{
	GENERATED_BODY()
	
public:

	UItems();

    virtual class UWorld* GetWorld() const { return World; };

    UPROPERTY()
    class UWorld* World;

    /**The text for using the item. (Equip, Eat, etc.)*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    FText UseActionText;

    /**The mesh to display for this items' pickup*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    class UStaticMesh* PickupMesh;

    /**The thumbnail for this item*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    class UTexture2D* Thumbnail;

    /**The display name for this item in the inventory*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    FText ItemDisplayName;

    /**An optional description for the item*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
    FText ItemDescription;

    /**The weight of the item*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
    float Weight;

    /**The inventory that owns the item*/
    UPROPERTY()
    class UReubInventoryComponent* OwningInventory;

    virtual void Use(class APlayground_511Character* Character);

    UFUNCTION(BlueprintImplementableEvent)
    void OnUse(class APlayground_511Character* Character);
};
