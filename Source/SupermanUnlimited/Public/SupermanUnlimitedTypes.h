// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SupermanUnlimitedTypes.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UGameplayAbility;


USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> Effects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	//class UCharacterAnimDataAsset* CharacterAnimDataAsset;
};
