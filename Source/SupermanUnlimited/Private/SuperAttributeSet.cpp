// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

void USuperAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxMovementSpeedAttribute())
	{
		ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningActor());
		UCharacterMovementComponent* CharacterMovement = OwningCharacter ? OwningCharacter->GetCharacterMovement() : nullptr;

		if (CharacterMovement)
		{
			const float MaxGroundSpeed = GetMaxMovementSpeed();

			CharacterMovement->MaxWalkSpeed = MaxGroundSpeed;
		}
	}
}

UFUNCTION()
void USuperAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, Health, OldHealth);
}

UFUNCTION()
void USuperAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, MaxHealth, OldMaxHealth);
}

void USuperAttributeSet::OnRep_Weakness(const FGameplayAttributeData& OldWeakness)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, Weakness, OldWeakness);
}

void USuperAttributeSet::OnRep_MaxWeakness(const FGameplayAttributeData& OldMaxWeakness)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, MaxWeakness, OldMaxWeakness);
}

void USuperAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, Strength, OldStrength);
}

void USuperAttributeSet::OnRep_MaxStrength(const FGameplayAttributeData& OldMaxStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, MaxStrength, OldMaxStrength);
}

void USuperAttributeSet::OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, MaxMovementSpeed, OldMaxMovementSpeed);
}

void USuperAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, Speed, OldSpeed);
}

void USuperAttributeSet::OnRep_MaxSpeed(const FGameplayAttributeData& OldMaxSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USuperAttributeSet, MaxSpeed, OldMaxSpeed);
}

void USuperAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, Weakness, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, MaxWeakness, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, MaxStrength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, MaxMovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USuperAttributeSet, MaxSpeed, COND_None, REPNOTIFY_Always);
}
