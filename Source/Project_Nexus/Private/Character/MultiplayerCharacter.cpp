// Copyright 2018-2024 In Series Studio GmbH
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/MultiplayerCharacter.h"

// Sets default values
AMultiplayerCharacter::AMultiplayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->TargetArmLength = 250.f;
	SpringArmComp->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	//SpringArmComp->SetRelativeRotation(FRotator(0.f,-90.f,0.f));


}

// Called when the game starts or when spawned
void AMultiplayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(GameplayMappingContext, 0);
		}

	}
	
}

// Called every frame
void AMultiplayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMultiplayerCharacter::Movement(const FInputActionValue& Value) {
	const FVector2D MoveValue = Value.Get<FVector2D>();

	//const FVector Forward = GetActorForwardVector();
	//const FVector Strafe = GetActorRightVector();

	//Directional movement
	//Get Controllers Rotation
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//coressponding to controller rotation who is pointing in
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (GetController()) {

		AddMovementInput(ForwardDirection, MoveValue.Y);
		AddMovementInput(RightDirection, MoveValue.X);

		UE_LOG(LogTemp, Warning, TEXT("Move X: %f  Y: %f "), MoveValue.X, MoveValue.Y);

	}
}

void AMultiplayerCharacter::LookForMouse(const FInputActionValue& Value) {
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController()) {
		AddControllerYawInput(LookAxisValue.X); //left and right
		AddControllerPitchInput(-1*LookAxisValue.Y); // up and down
		UE_LOG(LogTemp, Warning, TEXT("LookMouse X: %f  Y: %f "), LookAxisValue.X, LookAxisValue.Y);

	}

}

void AMultiplayerCharacter::LookForController(const FInputActionValue& Value) {
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController()) {
		AddControllerYawInput(LookAxisValue.X * (RotationRate * Sensibilty) * GetWorld()->GetDeltaSeconds()); //left and right
		AddControllerPitchInput(-1*(LookAxisValue.Y * (RotationRate * Sensibilty) *GetWorld()->GetDeltaSeconds())); // up and down
		UE_LOG(LogTemp, Warning, TEXT("LookMouse X: %f  Y: %f "), LookAxisValue.X, LookAxisValue.Y);

	}
}

// Called to bind functionality to input
void AMultiplayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComp->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMultiplayerCharacter::Movement);
		EnhancedInputComp->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &AMultiplayerCharacter::LookForMouse);
		EnhancedInputComp->BindAction(LookControllerAction, ETriggerEvent::Triggered, this, &AMultiplayerCharacter::LookForController);
	}

}

