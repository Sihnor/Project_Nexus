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

	if (GetController() && IsCombatReady && !IsBlocking && GetVelocity().Y == 0 && GetVelocity().Y == 0 && !WasFirstHeavyAttackUsed && !WasFirstLightAttackUsed) {
		AddMovementInput(Forward, Value.Get<float>());
		//UE_LOG(LogTemp, Warning, TEXT("Move X: %f"), Value.Get<float>());
	}
}

void AFightingCharacter::DoMoveBwd(const FInputActionValue& Value){
	const FVector Forward = GetActorForwardVector();

	if (GetController() && IsCombatReady && !IsBlocking && GetVelocity().Y == 0 && GetVelocity().Y == 0 && !WasFirstHeavyAttackUsed && !WasFirstLightAttackUsed) {
		AddMovementInput(Forward, Value.Get<float>());
		//UE_LOG(LogTemp, Warning, TEXT("Move X: %f"), Value.Get<float>());
	}
}

void AFightingCharacter::LightAttack(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		if(!WasFirstLightAttackUsed){
			WasFirstLightAttackUsed = true;
		}
		//UE_LOG(LogTemp, Warning, TEXT("Light Attack"));
		//UE_LOG(LogTemp, Warning, TEXT("LA: %d"), WasFirstLightAttackUsed);
	}
}

void AFightingCharacter::HeavyAttack(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		if(!WasFirstHeavyAttackUsed){
			WasFirstHeavyAttackUsed = true;
		}
		//UE_LOG(LogTemp, Warning, TEXT("Heavy Attack"));
		//UE_LOG(LogTemp, Warning, TEXT("HA: %d"), WasFirstHeavyAttackUsed);
	}
}

void AFightingCharacter::Block(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && !this->bIsCrouched) {
			IsBlocking = true;
			//UE_LOG(LogTemp, Warning, TEXT("Block"));
	}else {
		IsBlocking = false;
	}
}

void AFightingCharacter::UnBlock(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
			IsBlocking = false;
			//UE_LOG(LogTemp, Warning, TEXT("UnBlock"));
	}
}

void AFightingCharacter::DoJump(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && this->CanJump()) {
		//UE_LOG(LogTemp, Warning, TEXT("Jump"));
		this->Jump();
	}
}

void AFightingCharacter::Duck(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && this->CanCrouch()) {
		//UE_LOG(LogTemp, Warning, TEXT("Duck"));
		this->Crouch();
	}
}

void AFightingCharacter::UnDuck(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && !this->CanCrouch()) {
		//UE_LOG(LogTemp, Warning, TEXT("UnDuck"));
		this->UnCrouch();
	}
}

void AFightingCharacter::SideStepNY(const FInputActionValue& Value){
    const FVector SideStep = GetActorRightVector();
    if (GetController() && IsCombatReady && !IsBlocking && !IsSideStepPY && GetVelocity().X == 0.f && !this->bIsCrouched && GetVelocity().Z == 0) {
		IsSideStepNY = true;
		//this->LaunchCharacter(FVector(0.f,-250.f, 0.f), true, true);
        //UE_LOG(LogTemp, Warning, TEXT("Move Value: %f"), Value.Get<float>());
        //UE_LOG(LogTemp, Warning, TEXT("SideStep Negative Y"));
    }
}

void AFightingCharacter::SideStepPY(const FInputActionValue& Value){
    const FVector SideStep = GetActorRightVector();

    if (GetController() && IsCombatReady && !IsBlocking && !IsSideStepNY && GetVelocity().X == 0.f && !this->bIsCrouched && GetVelocity().Z == 0) {	
		IsSideStepPY = true;	
		//this->LaunchCharacter(FVector(0.f,250.f, 0.f), true, true);
		//AddMovementInput(SideStep, Value.Get<float>());
        //UE_LOG(LogTemp, Warning, TEXT("Move Value: %f"), Value.Get<float>());
        //UE_LOG(LogTemp, Warning, TEXT("SideStep Positive Y"));
    }
}

void AFightingCharacter::ClearSideStep(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		IsSideStepNY = false;
		IsSideStepPY = false;
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

		EnhancedInputComp->BindAction(LightAttackAction, ETriggerEvent::Started, this, &AFightingCharacter::LightAttack);
		EnhancedInputComp->BindAction(HeavyAttackAction, ETriggerEvent::Started, this, &AFightingCharacter::HeavyAttack);

		EnhancedInputComp->BindAction(BlockAction, ETriggerEvent::Triggered, this, &AFightingCharacter::Block);
		EnhancedInputComp->BindAction(BlockAction, ETriggerEvent::Completed, this, &AFightingCharacter::UnBlock);

		EnhancedInputComp->BindAction(SideStepPositiveYAction, ETriggerEvent::Triggered, this, &AFightingCharacter::SideStepPY);
		EnhancedInputComp->BindAction(SideStepNegativeYAction, ETriggerEvent::Triggered, this, &AFightingCharacter::SideStepNY);
		//EnhancedInputComp->BindAction(SideStepPositiveYAction, ETriggerEvent::Completed, this, &AFightingCharacter::ClearSideStep);
		//EnhancedInputComp->BindAction(SideStepNegativeYAction, ETriggerEvent::Completed, this, &AFightingCharacter::ClearSideStep);
	}

}

