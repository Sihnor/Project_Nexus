// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/HitBox.h"

// Sets default values
AHitBox::AHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SceneComp->SetupAttachment(RootComponent);

	HitboxDisplay = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hitbox Display"));
	HitboxDisplay->SetupAttachment(SceneComp);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	HitboxDisplay->SetStaticMesh(CubeMeshAsset.Object);

	HitboxDamage = 0.f;
	HitstunTime= 0.f;
	BlockstunTime= 0.f;
	PushbackDistance = 0.f;
	LaunchDistance = 0.f;
	HitStopTime = 0.f;


	ShouldAttach = false;
	IsNeutral = false;
	CauseGroundBounce = false;
}

// Called when the game starts or when spawned
void AHitBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

