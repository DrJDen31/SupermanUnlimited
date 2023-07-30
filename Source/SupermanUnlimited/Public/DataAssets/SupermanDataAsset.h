// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SuperDataAssetBase.h"
#include "SupermanDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANUNLIMITED_API USupermanDataAsset : public USuperDataAssetBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	TSubclassOf<class UGameplayAbility> FlyAbility;

};
