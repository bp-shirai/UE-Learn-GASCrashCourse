// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Framework/ActorPoolingInterface.h"
#include "CC_BaseCharacter.generated.h"

namespace CrashTags
{
    extern const FName Player;
    extern const FName Enemy;
} // namespace CrashTags

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAbilitySystemInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class CRASHCOURSE_API ACC_BaseCharacter : public ACharacter, public IAbilitySystemInterface, public IActorPoolingInterface
{
    GENERATED_BODY()

public:
    ACC_BaseCharacter();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return nullptr; }
    virtual UAttributeSet* GetAttributeSet() const { return nullptr; }

    bool IsAlive() const { return bAlive; }
    void SetAlive(bool Alive) { bAlive = Alive; }

    UPROPERTY(BlueprintAssignable)
    FAbilitySystemInitialized OnAbilitySystemInitialized;

    UFUNCTION(BlueprintCallable, Category = "Crash|Death")
    virtual void HandleRespawn();

    UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
    void ResetAttributes();

protected:
    void GiveStartupAbilities();
    void InitializeAttributes();

    void OnHealthChanged(const FOnAttributeChangeData& Data);
    virtual void HandleDeath();

private:
    UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
    TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
    TSubclassOf<UGameplayEffect> InitializeAttributesEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
    TSubclassOf<UGameplayEffect> ResetAttributesEffect;

    UPROPERTY(BlueprintReadOnly, Replicated, meta = (AllowPrivateAccess = "true"), Category = "Crash|Attributes")
    bool bAlive{true};

    void ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> ApplyEffect, int32 Level = 1);
};
