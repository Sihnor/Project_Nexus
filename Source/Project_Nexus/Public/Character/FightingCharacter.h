// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FightingCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

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

	//void 

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComp;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool MoveFwd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool MoveBwd;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsCombatReady = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool IsBlocking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool WasFirstLightAttackUsed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine", meta = (AllowPrivateAccess = "true"))
		bool WasFirstHeavyAttackUsed = false;

};
