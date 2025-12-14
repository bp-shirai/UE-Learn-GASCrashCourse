// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CC_BaseCharacter.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAbilitySystemInitialized, UAbilitySystemComponent*, ASC,  UAttributeSet*, AS);

UCLASS(Abstract)
class CRASHCOURSE_API ACC_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ACC_BaseCharacter();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return nullptr; }
    virtual UAttributeSet* GetAttributeSet() const { return nullptr; }

    UPROPERTY(BlueprintAssignable)
    FAbilitySystemInitialized OnAbilitySystemInitialized;

protected:
    void GiveStartupAbilities();
    void InitializeAttributes();


private:
    UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
    TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
    TSubclassOf<UGameplayEffect> InitializeAttributesEffect;
};
