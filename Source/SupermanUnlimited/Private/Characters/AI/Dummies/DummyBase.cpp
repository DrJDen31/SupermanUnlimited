// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/Dummies/DummyBase.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/AttributeSets/AttributeSetBase.h"

ADummyBase::ADummyBase()
{
	// Override size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// UNIQUE ATTRIBUTE SET
	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));
}