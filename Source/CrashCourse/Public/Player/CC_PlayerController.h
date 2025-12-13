// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CC_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


/**
 * 
 */
UCLASS(Abstract)
class CRASHCOURSE_API ACC_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Input")
	TObjectPtr<UInputAction> IA_Look;

	void Jump(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
