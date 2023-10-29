// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FightingCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFightingCharacter::AFightingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->TargetArmLength = 250.f;
	SpringArmComp->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	SpringArmComp->SetRelativeRotation(FRotator(0.f,-90.f,0.f));

}

// Called when the game starts or when spawned
void AFightingCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(GameplayMappingContext, 0);
		}
	}
	
}

// Called every frame
void AFightingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFightingCharacter::Movement(const FInputActionValue& Value){
	const FVector2D MoveValue = Value.Get<FVector2D>();
	const FVector Forward = GetActorForwardVector();

	//const FVector Forward = GetActorForwardVector();
	//const FVector Forward = GetActorForwardVector();
	//const FVector Strafe = GetActorRightVector();



	if (GetController() && IsCombatReady) {
		//UE_LOG(LogTemp, Warning, TEXT("Moving"));
		//UE_LOG(LogTemp, Warning, TEXT("Move X: %f Move Y: %f"), MoveValue.X, MoveValue.Y);
		UE_LOG(LogTemp, Warning, TEXT("Forward X: %f Foward Y: %f Forward Z: %f"), Forward.X, Forward.Y, Forward.Z);
		AddMovementInput(Forward, MoveValue.X);
		//UE_LOG(LogTemp, Warning, TEXT("Move X: %f\nMove Y: %f\nMove Z:"), MoveValue.X, MoveValue.Y, MoveValue.Z);
		//AddMovementInput(Forward, MoveValue.Y);
		//AddMovementInput(Strafe, MoveValue.X);
	}
}

void AFightingCharacter::LightAttack(const FInputActionValue& Value){
	
	if (GetController() && IsCombatReady) {
		UE_LOG(LogTemp, Warning, TEXT("Light Attack"));
	}
}

void AFightingCharacter::HeavyAttack(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		UE_LOG(LogTemp, Warning, TEXT("Heavy Attack"));
	}
}

void AFightingCharacter::Block(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		UE_LOG(LogTemp, Warning, TEXT("Block"));
	}
}

/*void AFightingCharacter::Jump(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		IsJumping = true;
		UE_LOG(LogTemp, Warning, TEXT("Jump"));
	}
}*/

void AFightingCharacter::Duck(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		UE_LOG(LogTemp, Warning, TEXT("Duck"));
	}
}

// Called to bind functionality to input
void AFightingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComp->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AFightingCharacter::Movement);
		EnhancedInputComp->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &AFightingCharacter::LightAttack);
		EnhancedInputComp->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &AFightingCharacter::HeavyAttack);
		EnhancedInputComp->BindAction(BlockAction, ETriggerEvent::Triggered, this, &AFightingCharacter::Block);
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFightingCharacter::Jump);
		EnhancedInputComp->BindAction(DuckAction, ETriggerEvent::Triggered, this, &AFightingCharacter::Duck);
	}

}

