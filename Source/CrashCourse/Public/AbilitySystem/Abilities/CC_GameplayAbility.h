// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CC_GameplayAbility.generated.h"

class UCC_AbilitySystemComponent;
class ACC_BaseCharacter;
class ACC_EnemyCharacter;

/**
 *
 */
UCLASS(Abstract)
class CRASHCOURSE_API UCC_GameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crash|Debug")
    bool bDrawDebug{false};

    UFUNCTION(BlueprintPure, Category = "Crash|Abilities")
    UCC_AbilitySystemComponent* GetCCAbilitySystemComponent() const;

    UFUNCTION(BlueprintPure, Category = "Crash|Abilities")
    ACC_BaseCharacter* GetCCBaseCharacter() const;

    UFUNCTION(BlueprintPure, Category = "Crash|Abilities")
    ACC_EnemyCharacter* GetCCEnemyCharacter() const;
};
