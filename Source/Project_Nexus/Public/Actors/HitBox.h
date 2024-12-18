// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitBox.generated.h"

//Begin: yellow
//Active: red
//Hurt: Blue
//Projectile: Pink
//Throw: light Green 
//Stun: Orange

UENUM(BlueprintType)
enum class EHitBoxStates : uint8
{
	HB_Begin UMETA(DisplayName = "Begin"),
    HB_Active UMETA(DisplayName = "Active"),
    HB_Hurtbox UMETA(DisplayName = "Hurtbox"),
	HB_Throwbox UMETA(DisplayName = "Throwbox")
	//HB_Projectile UMETA(DisplayName = "Projectile")
	//more...
};

UCLASS()
class PROJECT_NEXUS_API AHitBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Notify the HitboxBP calss Instance the hitbox is ready to be drawn
	//void TriggerVisualHitbox();

	//Draw hitbox to visualize it (for ddebugging or practice mode)
	//void VisualHitbox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float HitboxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float HitstunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float HitStopTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float BlockstunTime;

	//Amount of distance to push the character back
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float PushbackDistance;

	//Amount of distance to launch the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float LaunchDistance;

	//location to spawn hitbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FRotator HitboxRotation;

	//Hitbox enum instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		EHitBoxStates HitboxType;

	//location to spawn hitbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FVector HitboxLocation;

	//Should Hitbox be attached to the Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		bool ShouldAttach;

	//Should Hitbox be attached to the Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		bool IsNeutral;

	//Should Hitbox be attached to the Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		bool CauseGroundBounce;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* HitboxDisplay;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SceneComp;
};
