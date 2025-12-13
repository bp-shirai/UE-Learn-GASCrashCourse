// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CC_EnemyCharacter.h"

#include "AbilitySystem/CC_AbilitySystemComponent.h"

ACC_EnemyCharacter::ACC_EnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AbilitySystemComponent = CreateDefaultSubobject<UCC_AbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* ACC_EnemyCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void ACC_EnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
    if (IsValid(ASC))
    {
        ASC->InitAbilityActorInfo(this, this);
        
        if (HasAuthority())
        {
            GiveStartupAbilities();
        }
    }
}
