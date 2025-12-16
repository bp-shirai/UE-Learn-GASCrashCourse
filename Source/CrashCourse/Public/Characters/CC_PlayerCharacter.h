// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CC_BaseCharacter.h"
#include "CC_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAbilitySystemComponent;

/**
 *
 */
UCLASS(Abstract)
class CRASHCOURSE_API ACC_PlayerCharacter : public ACC_BaseCharacter
{
    GENERATED_BODY()

public:
    ACC_PlayerCharacter();
    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    virtual UAttributeSet* GetAttributeSet() const override;

    UFUNCTION(BlueprintCallable, Category = "Crash|Player")
    void SetInputEnableFromPlayerController(bool bEnable);

private:
    UPROPERTY(VisibleAnywhere, Category = "Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    TObjectPtr<UCameraComponent> FollowCamera;
};
