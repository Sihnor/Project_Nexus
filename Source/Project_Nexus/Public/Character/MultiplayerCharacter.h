// Copyright 2018-2024 In Series Studio GmbH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MultiplayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UENUM(BlueprintType)
enum class EMCharacterState : uint8
{
	MC_Default UMETA(DisplayName = "Idle"),
    MC_MovingForward UMETA(DisplayName = "Moving_Forward"),
	MC_Jumping UMETA(DisplayName = "Jumping"),
	MC_Gesture1 UMETA(DisplayName = "Angry"),
	MC_Gesture2 UMETA(DisplayName = "Happy"),
	MC_Gesture3 UMETA(DisplayName = "Dance"),
	MC_Gesture4 UMETA(DisplayName = "Greet")
	//more...
};

UCLASS()
class PROJECT_NEXUS_API AMultiplayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMultiplayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps) const override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* GameplayMappingContext;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LookMouseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LookControllerAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* Gesture1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* Gesture2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* Gesture3Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* Gesture4Action;

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void SvrRPCCharacterState(EMCharacterState _MCharacterState);

private:

	void Movement(const FInputActionValue& Value);

	void LookForMouse(const FInputActionValue& Value);

	void LookForController(const FInputActionValue& Value);

	void Gesture1(const FInputActionValue& Value);

	void Gesture2(const FInputActionValue& Value);

	void Gesture3(const FInputActionValue& Value);

	void Gesture4(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Sensibilty = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotationRate = 10;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Emotes", meta = (AllowPrivateAccess = "true"))
		EMCharacterState MCharacterState;

};
