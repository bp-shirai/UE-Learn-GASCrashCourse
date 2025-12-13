// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CC_BaseCharacter.h"

#include "Components/SkeletalMeshComponent.h"

ACC_BaseCharacter::ACC_BaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

}

