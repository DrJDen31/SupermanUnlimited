// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/AttributeSets/AttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "SuperAttributeSet.generated.h"

/**
 * 
 */

UCLASS()
class SUPERMANUNLIMITED_API USuperAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Weakness", ReplicatedUsing = OnRep_Weakness)
	FGameplayAttributeData Weakness;
	ATTRIBUTE_ACCESSORS(USuperAttributeSet, Weakness)

	UPROPERTY(BlueprintReadOnly, Category = "Weakness", ReplicatedUsing = OnRep_MaxWeakness)
	FGameplayAttributeData MaxWeakness;
	ATTRIBUTE_ACCESSORS(USuperAttributeSet, MaxWeakness)

	UPROPERTY(BlueprintReadOnly, Category = "Strength", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(USuperAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Strength", ReplicatedUsing = OnRep_MaxStrength)
	FGameplayAttributeData MaxStrength;
	ATTRIBUTE_ACCESSORS(USuperAttributeSet, MaxStrength)

	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(USuperAttributeSet, Speed)

	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_MaxSpeed)
	FGameplayAttributeData MaxSpeed;
	ATTRIBUTE_ACCESSORS(USuperAttributeSet, MaxSpeed)

protected:

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;

	UFUNCTION()
	virtual void OnRep_Weakness(const FGameplayAttributeData& OldWeakness);

	UFUNCTION()
	virtual void OnRep_MaxWeakness(const FGameplayAttributeData& OldMaxWeakness);

	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UFUNCTION()
	virtual void OnRep_MaxStrength(const FGameplayAttributeData& OldMaxStrength);

	UFUNCTION()
	virtual void OnRep_Speed(const FGameplayAttributeData& OldSpeed);

	UFUNCTION()
	virtual void OnRep_MaxSpeed(const FGameplayAttributeData& OldMaxSpeed);
};

