// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "Sword.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMesh"));
	CapsuleColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Colider"));
	SetRootComponent(SkeletalMesh);
	CapsuleColider->SetupAttachment(SkeletalMesh);

}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

