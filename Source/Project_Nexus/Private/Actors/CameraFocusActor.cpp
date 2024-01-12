// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/CameraFocusActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ACameraFocusActor::ACameraFocusActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SceneComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(SceneComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	/*SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	SphereMesh->SetupAttachment(SceneComp);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);*/

	SpringArmComp->TargetArmLength = 150.f;
	SceneComp->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	SpringArmComp->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	//CameraComp->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	SpringArmComp->SetRelativeRotation(FRotator(0.f,-90.f,0.f));

}

// Called when the game starts or when spawned
void ACameraFocusActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraFocusActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

