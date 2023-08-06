// Copyright Jaden Tompkins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SUPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class SUPERMANUNLIMITED_API ASUPlayerController : public APlayerController
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

public:

	ASUPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
};
