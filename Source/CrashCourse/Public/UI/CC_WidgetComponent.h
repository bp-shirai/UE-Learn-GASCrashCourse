// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AttributeSet.h"
#include "CC_WidgetComponent.generated.h"

class ACC_BaseCharacter;
class UCC_AbilitySystemComponent;
class UCC_AttributeSet;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 *
 */
UCLASS()
class CRASHCOURSE_API UCC_WidgetComponent : public UWidgetComponent
{
    GENERATED_BODY()
public:
    UCC_WidgetComponent();
    virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Crash|Attributes")
    TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:
    TWeakObjectPtr<ACC_BaseCharacter> OwnerCharacter;
    TWeakObjectPtr<UCC_AbilitySystemComponent> AbilitySystemComponent;
    TWeakObjectPtr<UCC_AttributeSet> AttributeSet;

    void InitAbilitySystemData();
    bool IsASCInitialized() const;
    void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

    UFUNCTION()
    void OnAbilitySystemInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);

    UFUNCTION()
    void BindToAttributeChanges();
};
