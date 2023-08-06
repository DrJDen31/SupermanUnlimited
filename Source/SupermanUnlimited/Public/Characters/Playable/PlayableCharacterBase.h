// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SuperCharacterBase.h"
#include "InputActionValue.h"
#include "PlayableCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANUNLIMITED_API APlayableCharacterBase : public ASuperCharacterBase
{
	GENERATED_BODY()
	
public:

	APlayableCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void PawnClientRestart() override;

protected:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
