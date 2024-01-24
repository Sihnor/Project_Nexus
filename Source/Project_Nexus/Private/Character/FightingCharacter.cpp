// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FightingCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Curves/CurveFloat.h"
#include "Character/FightingCharacter.h"
#include "Actors/HitBox.h"



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
	Hurtbox= nullptr;
	bUsingComplexHurtboxes = false;
	CharacterState = ECharacterState::FC_Default;
	Transform = FTransform();

	MaxDistanceApart = 800.f;
	StunTime = 0.f;
	RemoveInputFromInputBufferTime = 1.f;
	DefaultGravityScale = GetCharacterMovement()->GravityScale;
	GravityScaleModifier = 0.8f;

	WasLightAttackUsed = false;
	WasHeavyAttackUsed = false;

	IsCombatReady = false;
	MoveFwd = false;
	MoveBwd = false;
	IsBlocking = false;
	IsSideStepNY = false;
	IsSideStepPY = false;
	WasLaunched = false;
	WasStunned = false;
	HasLandedHit = false;
	IsKnockedDown = false;
	IsRecovery = false;
	IsWallBounce = false;
	IsGroundBounce = false;
	
	//Create a child class so every character has it's own command and create a database of it... Sorry
	TempCommand.CommandName = "Test Command";
	TempCommand.Inputs.Add("A");
	TempCommand.Inputs.Add("S");
	TempCommand.Inputs.Add("D");
	HasUsedTempCommand = false;
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



	//UE_LOG(LogTemp, Warning, TEXT("Forwar actor: %f"), GetActorForwardVector().X);
	//UE_LOG(LogTemp, Warning, TEXT("Player %i Was launched: %i"), PlayerIndex, WasLaunched);

	//UE_LOG(LogTemp, Warning, TEXT("0-> Player %i IsCombatReady: %i Launched: %i Stunned: %i KnockedDown: %i IsRecovery: %i IsOnGround: %i IsWallBounce: %i IsGroundBounce: %i"), PlayerIndex, IsCombatReady, WasLaunched, WasStunned, IsKnockedDown, IsRecovery, GetCharacterMovement()->IsMovingOnGround(), IsWallBounce, IsGroundBounce);

	//UE_LOG(LogTemp, Warning, TEXT("Player %i IsCombatReady: %i IsBlocking: %i HavyAttack: %i LightAttack: %i, IsSideStepNY: %i, IsSideStepPY: %i IsCrouched: %i Launched: %i Stunned: %i KnockedDown: %i IsRecovery: %i IsOnGround: %i"), PlayerIndex, IsCombatReady, IsBlocking, WasHeavyAttackUsed, WasLightAttackUsed,IsSideStepNY ,IsSideStepPY, this->bIsCrouched, WasLaunched, WasStunned, IsKnockedDown, IsRecovery, GetCharacterMovement()->IsMovingOnGround());

	//UE_LOG(LogTemp, Warning, TEXT("Player %i Launched: %i Stunned: %i KnockedDown: %i IsRecovery: %i IsOnGround: %i"), PlayerIndex, WasLaunched, WasStunned, IsKnockedDown, IsRecovery, GetCharacterMovement()->IsMovingOnGround());
	//UE_LOG(LogTemp, Warning, TEXT("Player %i NotLaunched: %i NotStunned: %i NotKnockedDown: %i NotIsRecovery: %i IsOnGround: %i"), PlayerIndex, !WasLaunched, !WasStunned, !IsKnockedDown, !IsRecovery, GetCharacterMovement()->IsMovingOnGround());

	//UE_LOG(LogTemp, Warning, TEXT("On Gorund: %i"), GetCharacterMovement()->IsMovingOnGround());
	//UE_LOG(LogTemp, Warning, TEXT("Player %i Rotation %f, %f, %f"), PlayerIndex, GetActorRotation().Roll, GetActorRotation().Pitch, GetActorRotation().Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("Player %i Foward Vector: %f"), PlayerIndex, GetActorForwardVector().X);

	//UE_LOG(LogTemp, Warning, TEXT("Velocit X: %f Y: %f Z: %f"), GetVelocity().X, GetVelocity().Y, GetVelocity().Z);
}


void AFightingCharacter::DoMoveFwd(const FInputActionValue& Value){
	const FVector Forward = GetActorForwardVector();

	if (GetController() && IsCombatReady && !IsBlocking && !WasHeavyAttackUsed && !WasLightAttackUsed && !IsSideStepNY && !IsSideStepPY && !this->bIsCrouched && !WasLaunched && !WasStunned && !IsKnockedDown && !IsRecovery && GetCharacterMovement()->IsMovingOnGround() && !IsWallBounce && !IsGroundBounce) {
		UpdateCharacterRotation();


		CharacterState = ECharacterState::FC_MovingForward;


		AddMovementInput(Forward, Value.Get<float>());

		MoveFwd = true;

		//UE_LOG(LogTemp, Warning, TEXT("Move Value X: %f"), Value.Get<float>());
		//UE_LOG(LogTemp, Warning, TEXT("Forwar Value: %f %f %f"), Forward.X, Forward.Y, Forward.Z);
	}/*else {
		CharacterState = ECharacterState::FC_Default;
	}*/

}

void AFightingCharacter::DoMoveBwd(const FInputActionValue& Value){
	const FVector Forward = GetActorForwardVector();

	if (GetController() && IsCombatReady && !IsBlocking && !WasHeavyAttackUsed && !WasLightAttackUsed && !IsSideStepNY && !IsSideStepPY && !this->bIsCrouched && !WasLaunched && !WasStunned && !IsKnockedDown && !IsRecovery && GetCharacterMovement()->IsMovingOnGround() && !IsWallBounce && !IsGroundBounce) {
		UpdateCharacterRotation();

		float CurrentDistanceApart = abs(OtherCharacter->GetActorLocation().X - GetActorLocation().X);

		/*UE_LOG(LogTemp, Warning, TEXT("Current distance %f"), CurrentDistanceApart);
		UE_LOG(LogTemp, Warning, TEXT("Current distance + Value %f"), CurrentDistanceApart + Value.Get<float>());
		UE_LOG(LogTemp, Warning, TEXT("Forwar actor is greater %i"), GetActorForwardVector().X > 0.f);
		UE_LOG(LogTemp, Warning, TEXT("Forwar actor %f"), GetActorForwardVector().X);*/

		if(CurrentDistanceApart >= MaxDistanceApart){
			if((CurrentDistanceApart + Value.Get<float>() > CurrentDistanceApart && GetActorForwardVector().X > 0.f) || (CurrentDistanceApart - Value.Get<float>() < CurrentDistanceApart && GetActorForwardVector().X < 0.f) ){
				AddMovementInput(Forward, Value.Get<float>());
			}
		}else {
			AddMovementInput(Forward, Value.Get<float>());
		}
		CharacterState = ECharacterState::FC_MovingBackward;
		MoveBwd = true;
		//UE_LOG(LogTemp, Warning, TEXT("Move X: %f"), Value.Get<float>());
	}/*else {
		CharacterState = ECharacterState::FC_Default;
	}*/
}

void AFightingCharacter::LightAttack(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		UpdateCharacterRotation();
		WasLightAttackUsed = true;

		//UE_LOG(LogTemp, Warning, TEXT("Light Attack"));
		//UE_LOG(LogTemp, Warning, TEXT("LA: %d"), WasFirstLightAttackUsed);
	}
}

void AFightingCharacter::HeavyAttack(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
		UpdateCharacterRotation();
		WasHeavyAttackUsed = true;
		
		//UE_LOG(LogTemp, Warning, TEXT("Heavy Attack"));
		//UE_LOG(LogTemp, Warning, TEXT("HA: %d"), WasFirstHeavyAttackUsed);
	}
}

void AFightingCharacter::Block(const FInputActionValue& Value){
	if (GetController() && IsCombatReady && !this->bIsCrouched && !WasHeavyAttackUsed && !WasLightAttackUsed) {
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
	if (GetController() && IsCombatReady && this->CanJump() && !WasStunned && !WasLaunched && !IsKnockedDown && !IsRecovery && !IsWallBounce && !IsGroundBounce) {
		//UE_LOG(LogTemp, Warning, TEXT("Jump"));
		this->Jump();

	}else if(IsKnockedDown){
		IsRecovery = true;
		IsKnockedDown = false;
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

    if (GetController() && IsCombatReady && !IsBlocking && !IsSideStepPY && !this->bIsCrouched && GetVelocity().Z == 0 && !MoveFwd && !MoveBwd && !WasHeavyAttackUsed && !WasLightAttackUsed && !WasLaunched && !WasStunned && !IsKnockedDown && !IsRecovery && GetCharacterMovement()->IsMovingOnGround()) {
		UpdateCharacterRotation();	
		IsSideStepNY = true;

		//this->LaunchCharacter(FVector(0.f,-250.f, 0.f), true, true);
        //UE_LOG(LogTemp, Warning, TEXT("Move Value: %f"), Value.Get<float>());
        //UE_LOG(LogTemp, Warning, TEXT("SideStep Negative Y"));
    }
}

void AFightingCharacter::SideStepPY(const FInputActionValue& Value){
    const FVector SideStep = GetActorRightVector();

    if (GetController() && IsCombatReady && !IsBlocking && !IsSideStepNY && !this->bIsCrouched && GetVelocity().Z == 0 && !MoveFwd && !MoveBwd  && !WasHeavyAttackUsed && !WasLightAttackUsed && !WasLaunched && !WasStunned && !IsKnockedDown && !IsRecovery && GetCharacterMovement()->IsMovingOnGround()) {	
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

		CharacterState = ECharacterState::FC_Default;
	}
}

void AFightingCharacter::DoAddInputToInputBuffer(const FInputActionValue& Value){
	if (GetController() && IsCombatReady) {
	
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

void AFightingCharacter::GetStunned(float HitStunTime, float BlockStunTime, float PushbackAmount, float LaunchAmount, bool IsNeutral)
{
	if(!IsBlocking){
		StunTime= HitStunTime;

		if(StunTime > 0.f){
			WasStunned = true;
			BeginStun();
		}

		if(OtherCharacter){
			OtherCharacter->HasLandedHit = true;
			OtherCharacter->PerformPushBack(PushbackAmount, 0.f, false, false);
		}

		PerformPushBack(PushbackAmount, LaunchAmount, false, IsNeutral);
	}else{
		StunTime = BlockStunTime;

		if(StunTime > 0.f){
			BeginStun();
		}

		if(OtherCharacter){
			OtherCharacter->HasLandedHit = false;
			OtherCharacter->PerformPushBack(PushbackAmount, LaunchAmount, false, IsNeutral);
			//OtherCharacter->PerformPushBack(PushbackAmount, 0.f, false, IsNeutral);
		}

		PerformPushBack(PushbackAmount, 0.f, true, false);
	}
}

void AFightingCharacter::PerformPushBack(float PushbackAmount, float LaunchAmount, bool HasBlocked, bool IsNeutral){
	if(HasBlocked){
		if(OtherCharacter->GetActorForwardVector().X < 0.f){
			LaunchCharacter(FVector( -PushbackAmount*2.f, 0.f,0.f), false, false);
			//UE_LOG(LogTemp, Warning, TEXT("1 Push Amount: %f"), -PushbackAmount*2.f);
		}else {
			LaunchCharacter(FVector(PushbackAmount*2.f, 0.f,0.f), false, false);
			//UE_LOG(LogTemp, Warning, TEXT("2 Push Amount: %f"), PushbackAmount*2.f);
		}
		
	}else {
		if(LaunchAmount>0.f || IsNeutral && !GetCharacterMovement()->IsMovingOnGround()){
				GetCharacterMovement()->GravityScale = DefaultGravityScale * GravityScaleModifier;
				GravityScaleModifier += 0.1f;
				WasLaunched = true;
				//UE_LOG(LogTemp, Warning, TEXT("0-> Player %i IsCombatReady: %i Launched: %i Stunned: %i KnockedDown: %i IsRecovery: %i IsOnGround: %i IsWallBounce: %i IsGroundBounce: %i"), PlayerIndex, IsCombatReady, WasLaunched, WasStunned, IsKnockedDown, IsRecovery, GetCharacterMovement()->IsMovingOnGround(), IsWallBounce, IsGroundBounce);
		}
		
		if(OtherCharacter->GetActorForwardVector().X < 0.f || OtherCharacter->GetActorForwardVector().Y < 0.f){
			
			if(IsNeutral && !GetCharacterMovement()->IsMovingOnGround()){
				//LaunchCharacter(FVector(-PushbackAmount, 0.f, 650.f), false, false);
				LaunchCharacter(FVector(-PushbackAmount, -PushbackAmount, 650.f), false, false);
			}else {
				//LaunchCharacter(FVector(-PushbackAmount, 0.f, LaunchAmount), false, false);
				LaunchCharacter(FVector(-PushbackAmount, -PushbackAmount, LaunchAmount), false, false);

			}
		}else{
			//UE_LOG(LogTemp, Warning, TEXT("Is neutral= %i and not ground = %i and Launch is %f"), IsNeutral, !GetCharacterMovement()->IsMovingOnGround(), LaunchAmount); //0.25
			if(IsNeutral && !GetCharacterMovement()->IsMovingOnGround()){
				//LaunchCharacter(FVector(PushbackAmount, 0.f, 650.f), false, false);
				LaunchCharacter(FVector(PushbackAmount, PushbackAmount, 650.f), false, false);
			}else {
				//LaunchCharacter(FVector(PushbackAmount, 0.f, LaunchAmount), false, false);
				LaunchCharacter(FVector(PushbackAmount, PushbackAmount, LaunchAmount), false, false);
			}
		}
	}
}

void AFightingCharacter::BeginStun(){
	IsCombatReady = false;

	GetWorld()->GetTimerManager().SetTimer(StunTimeHandle, this, &AFightingCharacter::EndStun, StunTime, false);

}

void AFightingCharacter::EndStun(){
	if(!WasLaunched && !IsKnockedDown && !IsRecovery && !IsWallBounce && !IsGroundBounce){
		IsCombatReady = true;
		WasStunned= false;
	}
}

void AFightingCharacter::Landed(const FHitResult& Hit){
	if(bWasJumping){
		if(!Cast<AHitBox>(Hit.GetActor())){
			GetCharacterMovement()->GravityScale = DefaultGravityScale;
			GravityScaleModifier = 0.8f;
			IsKnockedDown = false;
		}
		
	} else if((WasLaunched && !IsGroundBounce) || IsWallBounce ||  IsGroundBounce){
		if(!Cast<AHitBox>(Hit.GetActor())){
			GetCharacterMovement()->GravityScale = DefaultGravityScale;
			GravityScaleModifier = 0.8f;
			IsKnockedDown = true;
		}
	}
	else if(IsGroundBounce){
		IsGroundBounce = true;
	}
	WasLaunched = false;
	IsWallBounce = false;
	
}


void AFightingCharacter::AddInputToInputBuffer(FInputInfo InputInfo){

	InputBuffer.Add(InputInfo);
	CheckInputBufferForCommand();
}

void AFightingCharacter::CheckInputBufferForCommand(){
	int CorrectSequenceCounter = 0;

	for(int CommandInput = 0; CommandInput < InputBuffer.Num(); ++CommandInput ){
		for(int Input = 0; Input < InputBuffer.Num(); ++Input){
			if (Input  + CorrectSequenceCounter < InputBuffer.Num()){
				if(InputBuffer[Input + CorrectSequenceCounter].InputName.Compare(TempCommand.Inputs[CommandInput]) == 0){
					UE_LOG(LogTemp, Warning, TEXT("The Player added another input to the comand sequence."));
					++CorrectSequenceCounter;

					if(CorrectSequenceCounter == TempCommand.Inputs.Num()){
						StartCommand(TempCommand.CommandName);
					}

					break;
				}else{
					UE_LOG(LogTemp, Warning, TEXT("The Player broke the comand sequence."));
					CorrectSequenceCounter = 0;
				}
			}else{
				UE_LOG(LogTemp, Warning, TEXT("The Player is not yet finished with the command sequence."));
				CorrectSequenceCounter = 0;
			}
		}
	}
}

void AFightingCharacter::StartCommand(FString CommandName){
	if(CommandName.Compare(TempCommand.CommandName) == 0){
		UE_LOG(LogTemp, Warning, TEXT("The Character is using the command: %s."), *CommandName);
		HasUsedTempCommand = true;
	}
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

		EnhancedInputComp->BindAction(AddToInputBufferAction, ETriggerEvent::Triggered, this, &AFightingCharacter::DoAddInputToInputBuffer);
	}
}


