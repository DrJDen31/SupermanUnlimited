// Copyright Jaden Tompkins


#include "Player/Controllers/SupermanPlayerController.h"

#include "Characters/Playable/Heroes/Superman.h"
#include "Components/SuperCharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "InputActionValue.h"



// Called to bind functionality to input
void ASupermanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {

		//Flight
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Started, this, &ASupermanPlayerController::OnFlyPressed);

		//Boost
		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Started, this, &ASupermanPlayerController::OnBoostPressed);
		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Completed, this, &ASupermanPlayerController::OnBoostReleased);
	}
}

void ASupermanPlayerController::BeginPlay()
{
	SupermanCharacter = GetPawn<ASuperman>();
}

void ASupermanPlayerController::OnFlyPressed(const FInputActionValue& Value)
{
	if (!SupermanCharacter)
	{
		SupermanCharacter = GetPawn<ASuperman>();
	}

	SupermanCharacter->OnFlyPressed(Value);
}

void ASupermanPlayerController::OnBoostPressed(const FInputActionValue& Value)
{
	if (!SupermanCharacter)
	{
		SupermanCharacter = GetPawn<ASuperman>();
	}

	SupermanCharacter->OnBoostPressed(Value);
}

void ASupermanPlayerController::OnBoostReleased(const FInputActionValue& Value)
{
	if (!SupermanCharacter)
	{
		SupermanCharacter = GetPawn<ASuperman>();
	}

	SupermanCharacter->OnBoostPressed(Value);
}