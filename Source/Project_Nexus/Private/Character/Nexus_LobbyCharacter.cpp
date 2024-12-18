// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Nexus_LobbyCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


class UEnhancedInputLocalPlayerSubsystem;

// Sets default values
ANexus_LobbyCharacter::ANexus_LobbyCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANexus_LobbyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(GameplayMappingContext, 0);
		}
	}
}

// Called every frame
void ANexus_LobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANexus_LobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

