// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CC_AbilitySystemComponent.generated.h"

/**
 *
 */
UCLASS()
class CRASHCOURSE_API UCC_AbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    UCC_AbilitySystemComponent();

    virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
    virtual void OnRep_ActivateAbilities() override;

private:
    void HandleAutoActivateAbility(const FGameplayAbilitySpec& AbilitySpec);
};
