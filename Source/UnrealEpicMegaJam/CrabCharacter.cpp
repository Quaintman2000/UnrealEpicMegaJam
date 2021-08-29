// Fill out your copyright notice in the Description page of Project Settings.


#include "CrabCharacter.h"
#include "Engine/World.h"
#include "DamageableActor.h"

// Sets default values
ACrabCharacter::ACrabCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACrabCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACrabCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACrabCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACrabCharacter::FireWeapon()
{
	FHitResult hit = InstantShot();
	ADamageableActor* hitActor = Cast<ADamageableActor>(hit.Actor);
	if (hitActor && hitActor->isAttackable)
	{
		hitActor->TakeAttack();
	}

}

// Called to return what the shot hit
FHitResult ACrabCharacter::InstantShot()
{
	FVector rayLocation;
	FRotator rayRotation;
	FVector endTrace = FVector::ZeroVector;

	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		//playerController->GetPlayerViewPoint(rayLocation, rayRotation);
		rayLocation = playerController->GetPawn()->GetActorLocation();
		rayRotation = playerController->GetPawn()->GetActorRotation();
		endTrace = rayLocation + (rayRotation.Vector() * weaponRange);
	}

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(InstantShot), true, GetInstigator());
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, rayLocation, endTrace, ECC_Visibility, traceParams);

	return hit;
}

