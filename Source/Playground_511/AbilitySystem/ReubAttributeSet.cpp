// Fill out your copyright notice in the Description page of Project Settings.


#include "ReubAttributeSet.h"
#include "Net/UnrealNetwork.h"

UReubAttributeSet::UReubAttributeSet()
{
}

void UReubAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UReubAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UReubAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UReubAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
}

void UReubAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UReubAttributeSet, Health, OldHealth);
}

void UReubAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UReubAttributeSet, Stamina, OldStamina);
}

void UReubAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UReubAttributeSet, AttackPower, OldAttackPower);
}
