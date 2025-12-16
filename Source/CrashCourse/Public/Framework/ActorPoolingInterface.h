// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorPoolingInterface.generated.h"


UINTERFACE(MinimalAPI)
class UActorPoolingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRASHCOURSE_API IActorPoolingInterface
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent)
	void PoolBeginPlay();

	UFUNCTION(BlueprintNativeEvent)
	void PoolEndPlay();
};
