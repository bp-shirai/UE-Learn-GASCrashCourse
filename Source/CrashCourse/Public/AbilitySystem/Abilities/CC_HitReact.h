// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CC_GameplayAbility.h"
#include "CC_HitReact.generated.h"

/**
 *
 */
UCLASS(Abstract)
class CRASHCOURSE_API UCC_HitReact : public UCC_GameplayAbility
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
    void CacheHitDirectionVectors(const AActor* Instigator);

    UPROPERTY(BlueprintReadOnly, Category = "Crash|Abilities")
    FVector AvatarForward;

    UPROPERTY(BlueprintReadOnly, Category = "Crash|Abilities")
    FVector ToInstigator;
};
