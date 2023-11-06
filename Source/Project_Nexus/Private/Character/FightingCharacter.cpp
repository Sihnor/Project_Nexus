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

void AFightingCharacter::DoMoveFwd(const FInputActionValue& Value){
	const FVector Forward = GetActorForwardVector();

	if (GetController() && IsCombatReady) {
		AddMovementInput(Forward, Value.Get<float>());
		//UE_LOG(LogTemp, Warning, TEXT("Move X: %f"), Value.Get<float>());
	}
}

void AFightingCharacter::DoMoveBwd(const FInputActionValue& Value){
	const FVector Forward = GetActorForwardVector();

	if (GetController() && IsCombatReady) {
		AddMovementInput(Forward, Value.Get<float>());
		//UE_LOG(LogTemp, Warning, TEXT("Move X: %f"), Value.Get<float>());
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

void AFightingCharacter::DoJump(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && this->CanJump()) {
		UE_LOG(LogTemp, Warning, TEXT("Jump"));
		this->Jump();
	}
}

void AFightingCharacter::Duck(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && this->CanCrouch()) {
		UE_LOG(LogTemp, Warning, TEXT("Duck"));
		this->Crouch();
	}
}

void AFightingCharacter::UnDuck(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && !this->CanCrouch()) {
		UE_LOG(LogTemp, Warning, TEXT("UnDuck"));
		this->UnCrouch();
	}
}

// Called to bind functionality to input
void AFightingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		/*Maybe Change Function Name*/
		EnhancedInputComp->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AFightingCharacter::DoMoveFwd);
		EnhancedInputComp->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &AFightingCharacter::DoMoveBwd);

		EnhancedInputComp->BindAction(DuckAction, ETriggerEvent::Triggered, this, &AFightingCharacter::Duck);
		EnhancedInputComp->BindAction(DuckAction, ETriggerEvent::Completed, this, &AFightingCharacter::UnDuck);
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFightingCharacter::DoJump);

		EnhancedInputComp->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &AFightingCharacter::LightAttack);
		EnhancedInputComp->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &AFightingCharacter::HeavyAttack);
		EnhancedInputComp->BindAction(BlockAction, ETriggerEvent::Triggered, this, &AFightingCharacter::Block);
	}

}

