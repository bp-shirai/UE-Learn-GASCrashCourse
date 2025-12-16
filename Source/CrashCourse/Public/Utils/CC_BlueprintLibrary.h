// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Utils/CC_GameTypes.h"
#include "CC_BlueprintLibrary.generated.h"

class UAbilitySystemComponent;
class ACharacter;
/**
 *
 */
UCLASS()
class CRASHCOURSE_API UCC_BlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "Crash|Utils")
    static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);

    UFUNCTION(BlueprintPure, Category = "Crash|Utils")
    static FName GetHitDirectionName(const EHitDirection& HitDirection);

    UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
    static bool ApplyGameplayTagInNone(UAbilitySystemComponent* TargetASC, const FGameplayTag& Tag);

    UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
    static bool RemoveGameplayTagInFound(UAbilitySystemComponent* TargetASC, const FGameplayTag& Tag);

    UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
    static void SetRagdollEnable(bool bEnable, ACharacter* Character);
};
