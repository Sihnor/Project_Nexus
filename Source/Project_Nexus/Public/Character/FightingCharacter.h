// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "FightingCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCurveFloat;
class AHitBox;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	FC_Default UMETA(DisplayName = "Not_Moving"),
    FC_MovingRight UMETA(DisplayName = "Moving_Right"),
    FC_MovingLeft UMETA(DisplayName = "Moving_Left"),
	FC_RunningLeft UMETA(DisplayName = "Running_Left"),
	FC_Jumping UMETA(DisplayName = "Jumping"),
	FC_Stunned UMETA(DisplayName = "Stunned"),
	FC_Blocking UMETA(DisplayName = "Blocking"),
	FC_Crouching UMETA(DisplayName = "Crouching"),
	FC_Launched UMETA(DisplayName = "Launched"),
	FC_KockedDown UMETA(DisplayName = "Knocked_Down"),
	FC_Recovery UMETA(DisplayName = "Recovery"),
	FC_WallBounce UMETA(DisplayName = "Wall_Bounce"),
	FC_GroundBounce UMETA(DisplayName = "Ground_Bounce")
	//more...
};

UCLASS()
class PROJECT_NEXUS_API AFightingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFightingCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* GameplayMappingContext;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveBackwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LightAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* HeavyAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* BlockAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* DuckAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* SideStepPositiveYAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* SideStepNegativeYAction;

	// Expose OtherPlayerCharacter to Blueprint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
    	AFightingCharacter* OtherPlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UTimelineComponent* TimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hurtboxes")
		AActor* Hurtbox;

	//Simple Hurtbox Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hurtboxes")
		TArray<AHitBox*> SimpleHurtboxArray;

	//Complex Hurtbox Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hurtboxes")
		TArray<UStaticMeshComponent*> ComplexHurtboxArray;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hurtboxes")
    	bool bUsingComplexHurtboxes;

	UFUNCTION(BlueprintCallable, Category = "Hitbox")
		void GetStunned(float HitStunTime, float BlockStunTime, float PushbackAmount, float LaunchAmount, bool IsNeutral);

	//Delegate signature for the function which will handle our Finished event.
	
   	FOnTimelineFloat TimelineProgressEvent;

	FOnTimelineEvent TimelineFinishedEvent;

    UFUNCTION(BlueprintCallable, Category = "Timeline")
        void TimelineProgressFunction(float Value);

	UFUNCTION(BlueprintCallable, Category = "Timeline")
        void TimelineFinishedFunction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
    	UCurveFloat* FloatCurve;

private:

	void DoMoveFwd(const FInputActionValue& Value); //include InputActionValue header file because it not a pointer

	void DoMoveBwd(const FInputActionValue& Value); //include InputActionValue header file because it not a pointer

	void SideStepPY(const FInputActionValue& Value);

	void SideStepNY(const FInputActionValue& Value);

	void LightAttack(const FInputActionValue& Value); //include InputActionValue header file because it not a pointer

	void HeavyAttack(const FInputActionValue& Value); //include InputActionValue header file because it not a pointer

	void Block(const FInputActionValue& Value); //include InputActionValue header file because it not a pointer

	void UnBlock(const FInputActionValue& Value); //include InputActionValue header file because it not a pointer

	void DoJump(const FInputActionValue& Value);
	
	void Duck(const FInputActionValue& Value); //include InputActionValue header file because it not a pointer

	void UnDuck(const FInputActionValue& Value);

	void ClearSideStep(const FInputActionValue& Value);

	//void GetStunned(float HitStunTime, float BlockStunTime, float PushbackAmount, float LaunchAmount);

	void PerformPushBack(float PushbackAmount, float LaunchAmount, bool HasBlocked, bool IsNeutral);

	void BeginStun();

	void EndStun();

	FTimerHandle StunTimeHandle;

	// Custom function for updating character rotation
	UFUNCTION(BlueprintCallable, Category = "Custom Character Rotation", meta = (AllowPrivateAccess = "true"))
    	void UpdateCharacterRotation();

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComp;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats" ,meta = (AllowPrivateAccess = "true"))
		AFightingCharacter* OtherCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool MoveFwd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool MoveBwd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsCombatReady = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsBlocking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool WasFirstLightAttackUsed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool WasFirstHeavyAttackUsed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsSideStepNY = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsSideStepPY = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool WasLaunched = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool WasStunned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool HasLandedHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsKnockedDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsRecovery = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsWallBounce = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsGroundBounce = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		float StunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		float DefaultGravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float GravityScaleModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		float MaxDistanceApart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
		int PlayerIndex;




    // Whether to rotate the character based on input
	/*UPROPERTY(EditAnywhere, Category = "Custom Character Rotation")
    	bool bRotateToFacePlayer;*/

	// Sensitivity for rotating the character
    UPROPERTY(EditAnywhere, Category = "Custom Character Rotation")
    	float RotationRate;

	UPROPERTY(EditAnywhere, Category = "Custom Character Rotation")
		float RotationMultiplier;

	UPROPERTY(EditAnywhere, Category = "Custom Character Rotation")
    	bool bShowRotation;

};
