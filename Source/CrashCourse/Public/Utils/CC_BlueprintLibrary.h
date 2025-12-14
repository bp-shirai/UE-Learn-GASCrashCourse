// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Utils/CC_GameTypes.h"
#include "CC_BlueprintLibrary.generated.h"

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
};
