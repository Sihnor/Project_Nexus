// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FightingCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Curves/CurveFloat.h"
#include "Character/FightingCharacter.h"


// Sets default values
AFightingCharacter::AFightingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);*/

	TimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));

	/*SpringArmComp->TargetArmLength = 250.f;
	SpringArmComp->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	SpringArmComp->SetRelativeRotation(FRotator(0.f,-90.f,0.f));*/

	OtherCharacter = nullptr;

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

	if (FloatCurve != nullptr){
		TimelineProgressEvent.BindUFunction(this, FName("TimelineProgressFunction"));
		TimelineFinishedEvent.BindUFunction(this, FName("TimelineFinishedFunction"));
		TimelineComp->AddInterpFloat(FloatCurve, TimelineProgressEvent);
        TimelineComp->SetTimelineFinishedFunc(TimelineFinishedEvent);
	}
	
}

// Called every frame
void AFightingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OtherCharacter = Cast<AFightingCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), PlayerIndex));	

	//UE_LOG(LogTemp, Warning, TEXT("Velocit X: %f Y: %f Z: %f"), GetVelocity().X, GetVelocity().Y, GetVelocity().Z);
}

void AFightingCharacter::DoMoveFwd(const FInputActionValue& Value){
	const FVector Forward = GetActorForwardVector();

	if (GetController() && IsCombatReady && !IsBlocking && !WasFirstHeavyAttackUsed && !WasFirstLightAttackUsed && !IsSideStepNY && !IsSideStepPY) {
		UpdateCharacterRotation();
		AddMovementInput(Forward, Value.Get<float>());
		MoveFwd = true;

		//UE_LOG(LogTemp, Warning, TEXT("Move Value X: %f"), Value.Get<float>());
		//UE_LOG(LogTemp, Warning, TEXT("Forwar Value: %f %f %f"), Forward.X, Forward.Y, Forward.Z);
	}

}

void AFightingCharacter::DoMoveBwd(const FInputActionValue& Value){
	const FVector Forward = GetActorForwardVector();

	if (GetController() && IsCombatReady && !IsBlocking && !WasFirstHeavyAttackUsed && !WasFirstLightAttackUsed && !IsSideStepNY && !IsSideStepPY && !this->bIsCrouched) {
		UpdateCharacterRotation();
		AddMovementInput(Forward, Value.Get<float>());
		MoveBwd = true;
		//UE_LOG(LogTemp, Warning, TEXT("Move X: %f"), Value.Get<float>());
	}
}

void AFightingCharacter::LightAttack(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		UpdateCharacterRotation();
		WasFirstLightAttackUsed = true;

		//UE_LOG(LogTemp, Warning, TEXT("Light Attack"));
		//UE_LOG(LogTemp, Warning, TEXT("LA: %d"), WasFirstLightAttackUsed);
	}
}

void AFightingCharacter::HeavyAttack(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		UpdateCharacterRotation();
		WasFirstHeavyAttackUsed = true;
		
		//UE_LOG(LogTemp, Warning, TEXT("Heavy Attack"));
		//UE_LOG(LogTemp, Warning, TEXT("HA: %d"), WasFirstHeavyAttackUsed);
	}
}

void AFightingCharacter::Block(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && !this->bIsCrouched && !WasFirstHeavyAttackUsed && !WasFirstLightAttackUsed) {
			UpdateCharacterRotation();
			IsBlocking = true;
			//UE_LOG(LogTemp, Warning, TEXT("Block"));
	}else {
		IsBlocking = false;
	}
}

void AFightingCharacter::UnBlock(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
			UpdateCharacterRotation();
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
		this->Crouch();

		//UE_LOG(LogTemp, Warning, TEXT("Duck"));
	}
}

void AFightingCharacter::UnDuck(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && !this->CanCrouch()) {
		this->UnCrouch();

		//UE_LOG(LogTemp, Warning, TEXT("UnDuck"));
	}
}

void AFightingCharacter::SideStepNY(const FInputActionValue& Value){
    const FVector SideStep = GetActorRightVector();

    if (GetController() && IsCombatReady && !IsBlocking && !IsSideStepPY && !this->bIsCrouched && GetVelocity().Z == 0 && !MoveFwd && !MoveBwd && !WasFirstHeavyAttackUsed && !WasFirstLightAttackUsed) {
		UpdateCharacterRotation();	
		IsSideStepNY = true;

		//this->LaunchCharacter(FVector(0.f,-250.f, 0.f), true, true);
        //UE_LOG(LogTemp, Warning, TEXT("Move Value: %f"), Value.Get<float>());
        //UE_LOG(LogTemp, Warning, TEXT("SideStep Negative Y"));
    }
}

void AFightingCharacter::SideStepPY(const FInputActionValue& Value){
    const FVector SideStep = GetActorRightVector();

    if (GetController() && IsCombatReady && !IsBlocking && !IsSideStepNY && !this->bIsCrouched && GetVelocity().Z == 0 && !MoveFwd && !MoveBwd  && !WasFirstHeavyAttackUsed && !WasFirstLightAttackUsed) {	
		UpdateCharacterRotation();	
		IsSideStepPY = true;

		//this->LaunchCharacter(FVector(0.f,250.f, 0.f), true, true);
		//AddMovementInput(SideStep, Value.Get<float>());
        //UE_LOG(LogTemp, Warning, TEXT("Move Value: %f"), Value.Get<float>());
        //UE_LOG(LogTemp, Warning, TEXT("SideStep Positive Y"));
    }
}

void AFightingCharacter::ClearSideStep(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		UpdateCharacterRotation();
		//IsSideStepNY = false;
		//IsSideStepPY = false;
		MoveFwd = false;
		MoveBwd = false;
	}
}

// Custom function for updating character rotation
void AFightingCharacter::UpdateCharacterRotation()
{
	if(OtherCharacter != nullptr){
		float TempRotaionRate;

		if(IsSideStepNY || IsSideStepPY){
			TempRotaionRate= RotationRate*RotationMultiplier;
		}else{
			TempRotaionRate=RotationRate;
		}
		
		if (TimelineComp != nullptr){
			TimelineComp->Play();
		}

		//UE_LOG(LogTemp, Warning, TEXT("found %f"), OtherCharacter->GetActorLocation().X);
		/*FRotator PlayerSetRotaion = FMath::RInterpTo(
			GetActorRotation(),
			UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),OtherCharacter->GetActorLocation()),
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 
			TempRotaionRate
		);*/

		//UE_LOG(LogTemp, Warning, TEXT("Rotation Rate %f"), TempRotaionRate);

		//SetActorRotation(FRotator(0.f, PlayerSetRotaion.Yaw, 0.f));
	}

}

void AFightingCharacter::TimelineProgressFunction(float Value){
	FRotator NewPlayerRot= FMath::Lerp(GetActorRotation(),UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),OtherCharacter->GetActorLocation()), Value);
	
	//UE_LOG(LogTemp, Warning, TEXT("Progress Value: %f"), Value);
	//UE_LOG(LogTemp, Warning, TEXT("Yaw Value: %f"),NewPlayerRot.Yaw);
	SetActorRotation(FRotator(0.f, NewPlayerRot.Yaw, 0.f));
}

void AFightingCharacter::TimelineFinishedFunction()
{
	TimelineComp->Stop();
	TimelineComp->SetPlaybackPosition(0.f, false);
}

// Called to bind functionality to input
void AFightingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		/*Maybe Change Function Name*/
		EnhancedInputComp->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AFightingCharacter::DoMoveFwd);
		EnhancedInputComp->BindAction(MoveForwardAction, ETriggerEvent::Completed, this, &AFightingCharacter::ClearSideStep);
		EnhancedInputComp->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &AFightingCharacter::DoMoveBwd);
		EnhancedInputComp->BindAction(MoveBackwardAction, ETriggerEvent::Completed, this, &AFightingCharacter::ClearSideStep);

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


