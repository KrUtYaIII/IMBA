// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "ItemPromtArrow.generated.h"

UCLASS()
class MYPROJECT9_API AItemPromtArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPromtArrow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;
};
