// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/BinaryCameraPawn.h"

ABinaryCameraPawn::ABinaryCameraPawn(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCylinder"));
	SetRootComponent(CapsuleComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	
	GameplayCameraComponent = CreateDefaultSubobject<UGameplayCameraComponent>(TEXT("GameplayCameraComponent"));
}

void ABinaryCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(DefaultCameraAsset && PlayerController)
	{
		GameplayCameraComponent->Camera = DefaultCameraAsset;
		GameplayCameraComponent->ActivateCameraForPlayerController(PlayerController);
	}
}
