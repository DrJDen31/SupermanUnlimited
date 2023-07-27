// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SupermanUnlimitedTypes.h"
#include "SuperDataAssetBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SUPERMANUNLIMITED_API USuperDataAssetBase : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	FCharacterData CharacterData;
};
