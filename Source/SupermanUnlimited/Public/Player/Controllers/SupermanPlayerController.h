// Copyright Jaden Tompkins

#pragma once

#include "CoreMinimal.h"
#include "Player/Controllers/SUPlayerController.h"
#include "SupermanPlayerController.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class SUPERMANUNLIMITED_API ASupermanPlayerController : public ASUPlayerController
{
	GENERATED_BODY()
	
	/** Fly Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FlyAction;

	/** Boost Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> BoostAction;


protected:

	class ASuperman* SupermanCharacter;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	void OnFlyPressed(const FInputActionValue& Value);
	void OnBoostPressed(const FInputActionValue& Value);
	void OnBoostReleased(const FInputActionValue& Value);
};
