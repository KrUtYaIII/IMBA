// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrates.h"
#include "Upgrates_AmmoPack.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AUpgrates_AmmoPack : public AUpgrates
{
	GENERATED_BODY()
public:
	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player) override;
};
