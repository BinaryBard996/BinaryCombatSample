// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BinaryCharacter.h"

#include "Ability/BinaryAbilitySystemComponent.h"

// Sets default values
ABinaryCharacter::ABinaryCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABinaryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABinaryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABinaryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

