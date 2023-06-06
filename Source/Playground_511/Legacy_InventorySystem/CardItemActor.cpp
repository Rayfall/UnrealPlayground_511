// Fill out your copyright notice in the Description page of Project Settings.


#include "CardItemActor.h"
#include "InventoryComponent.h"
#include "../Playground_511Character.h"

ACardItemActor::ACardItemActor()
{

}

void ACardItemActor::Use(APlayground_511Character* Character)
{
	if (Character) {

		if (HealToHealth > 0) {
			Character->Health += HealToHealth;
		}

		if (DamageToActor > 0) {
			UE_LOG(LogTemp, Warning, TEXT("Initiated an attack to the actor"));
		}

		if (AddToArmor > 0) {
			Character->Armor += AddToArmor;
		}

		if (OwningInventory && (NumberOf < 2)) {
			OwningInventory->RemoveItem(this);
		}
	}
}

bool ACardItemActor::TraceHitResult()
{
	/*
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	// We set up a line trace from our current location to a point 1000cm ahead of us
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 1000.0f;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
		return true;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
		return false;
	}
	*/
	return false;
}