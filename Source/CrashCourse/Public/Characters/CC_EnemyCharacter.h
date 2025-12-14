// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CC_BaseCharacter.h"
#include "CC_EnemyCharacter.generated.h"

class UAbilitySystemComponent;
//class UCC_AttributeSet;
class UAttributeSet;

/**
 * 
 */
UCLASS(Abstract)
class CRASHCOURSE_API ACC_EnemyCharacter : public ACC_BaseCharacter
{
	GENERATED_BODY()

public:
	ACC_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
