// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TakableProjectile.generated.h"

class AWeapon_Level;
/**
 * 
 */
UCLASS()
class MYPROJECT9_API ATakableProjectile : public AWeapon_Projectile
{
	GENERATED_BODY()
	
public:
	ATakableProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* MyCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MyGunMesh;

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnWeapLevel();

	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundHitChel();

	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundHitNotChel();

	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(EditAnywhere, Category = "WeaponLevel_Class")
		TSubclassOf<AWeapon_Level> WeaponLevel_Class;
};
