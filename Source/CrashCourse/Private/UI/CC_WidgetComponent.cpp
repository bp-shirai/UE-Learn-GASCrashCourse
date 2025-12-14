// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CC_WidgetComponent.h"

#include "AbilitySystem/CC_AbilitySystemComponent.h"
#include "AbilitySystem/CC_AttributeSet.h"
#include "Characters/CC_BaseCharacter.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/WidgetTree.h"

#include "UI/CC_AttributeWidget.h"

UCC_WidgetComponent::UCC_WidgetComponent()
{
}

void UCC_WidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    InitAbilitySystemData();

    if (!IsASCInitialized())
    {
        OwnerCharacter->OnAbilitySystemInitialized.AddDynamic(this, &ThisClass::OnAbilitySystemInitialized);
    }
    else
    {
        InitializeAttributeDelegate();
    }
}

void UCC_WidgetComponent::InitAbilitySystemData()
{
    OwnerCharacter         = Cast<ACC_BaseCharacter>(GetOwner());
    AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
    AttributeSet           = Cast<UCC_AttributeSet>(OwnerCharacter->GetAttributeSet());
}

bool UCC_WidgetComponent::IsASCInitialized() const
{
    return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UCC_WidgetComponent::OnAbilitySystemInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    UE_LOG(LogTemp, Warning, TEXT("UCC_WidgetComponent::OnAbilitySystemInitialized : %s"), *OwnerCharacter->GetName());

    AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(ASC);
    AttributeSet           = Cast<UCC_AttributeSet>(AS);

    // Check if the Attribute Set has been Initialized with the first GE
    // If not, bind to some delegate that will be broadcast when it is initialized.
    if (!IsASCInitialized())
    {
        UE_LOG(LogTemp, Error, TEXT("Owner AbilitySystemComponent was not initialized."));
        return;
    }

    InitializeAttributeDelegate();
}

void UCC_WidgetComponent::InitializeAttributeDelegate()
{
    if (!AttributeSet->bAttributeInitialized)
    {
        AttributeSet->OnAttributeInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
    }
    else
    {
        BindToAttributeChanges();
    }
}

void UCC_WidgetComponent::BindToAttributeChanges()
{
    // Listen for changed to Gameplay Attributes and update our widgets accordingly.
    for (const auto& Pair : AttributeMap)
    {
        // Otherwise, loop over all children on the owned widget, and do the some for them.
        BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); // for checking the owned widget object.

        GetUserWidgetObject()->WidgetTree->ForEachWidget(
            [this, &Pair](UWidget* ChildWidget)
            {
                BindWidgetToAttributeChanges(ChildWidget, Pair);
            });
    }
}

void UCC_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
    // Check the user widget object owner by this component, see if it is a CC_AttributeWidget, handle it if so.
    UCC_AttributeWidget* AttributeWidget = Cast<UCC_AttributeWidget>(WidgetObject);
    if (!IsValid(AttributeWidget)) return;                // We only care about CC Attribute Widgets
    if (!AttributeWidget->MatchesAttribute(Pair)) return; // Only subscribe for matching Attributes

    AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // for initial values.

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda(
        [this, AttributeWidget, &Pair](const FOnAttributeChangeData AttributeChangeData)
        {
            AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // For changed during the game.
        });
}
