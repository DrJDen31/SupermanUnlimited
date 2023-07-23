// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SupermanUnlimitedTypes.h"
#include "SupermanDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANUNLIMITED_API USupermanDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FCharacterData CharacterData;
};
