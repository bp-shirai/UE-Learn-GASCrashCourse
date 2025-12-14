// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AttributeSet.h"
#include "CC_AttributeChangeTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

struct FOnAttributeChangeData;

/**
 *
 */
UCLASS()
class CRASHCOURSE_API UCC_AttributeChangeTask : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnAttributeChanged OnAttributeChanged;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
    static UCC_AttributeChangeTask* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

    UFUNCTION(BlueprintCallable)
    void EndTask();

private:
    TWeakObjectPtr<UAbilitySystemComponent> OwnerASC;
    FGameplayAttribute AttributeToListenFor;

    void AttributeChanged(const FOnAttributeChangeData& Data);
};
