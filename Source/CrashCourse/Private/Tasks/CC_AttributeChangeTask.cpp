// Fill out your copyright notice in the Description page of Project Settings.

#include "Tasks/CC_AttributeChangeTask.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

UCC_AttributeChangeTask* UCC_AttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
    UCC_AttributeChangeTask* NewTask = NewObject<UCC_AttributeChangeTask>();
    NewTask->OwnerASC                = AbilitySystemComponent;
    NewTask->AttributeToListenFor    = Attribute;

    if (!IsValid(AbilitySystemComponent))
    {
        NewTask->RemoveFromRoot();
        return nullptr;
    }

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(NewTask, &ThisClass::AttributeChanged);

    return NewTask;
}

void UCC_AttributeChangeTask::EndTask()
{
    if (UAbilitySystemComponent* ASC = OwnerASC.Get())
    {
        ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
    }

    SetReadyToDestroy();
    MarkAsGarbage();
}

void UCC_AttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
    // Data.GEModData->EffectSpec.GetEffectContext().GetInstigator();

    // GetEffectContext().GetInstigator()
    OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
