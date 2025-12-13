// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "CC_PlayerState.generated.h"



/**
 *
 */
UCLASS(Abstract)
class CRASHCOURSE_API ACC_PlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ACC_PlayerState();

    UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Crash|Abilities")
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
