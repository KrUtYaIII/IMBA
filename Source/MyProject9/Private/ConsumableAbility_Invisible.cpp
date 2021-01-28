// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_Invisible.h"
#include "Chel.h"
#include "GS.h"
#include "InteractiveCache.h"

FVector UConsumableAbility_Invisible::GetCacheScale3D(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UConsumableAbility_Invisible::GetCacheRotation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return FRotator(GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UConsumableAbility_Invisible::GetCacheLocation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetLocation();
}

void UConsumableAbility_Invisible::UseAbilityServer(AChel* Player)
{
	if (!Player->IsNowInvisible)
		Player->InvisibleEverywhere();
	else
	{
		Player->LastInvisibleAbilityObj->DestroyNonNativeProperties();
		Player->World->GetTimerManager().ClearTimer(Player->TimerHandleInvisible);
	}
	Player->LastInvisibleAbilityObj = this;
	Player->IsNowInvisible = true;
	TmpPlayer = Player;
	GetWorld()->GetTimerManager().SetTimer(Player->TimerHandleInvisible, this, &UConsumableAbility_Invisible::EndEffect, Duration, false);
}

void UConsumableAbility_Invisible::EndEffect()
{
	TmpPlayer->IsNowInvisible = false;
	TmpPlayer->ReverceInvisibleEverywhere();
	TmpPlayer->LastInvisibleAbilityObj = nullptr;
	TmpPlayer->UserView->RemoveIconFromPanel(IdentificatorIcon);
	DestroyNonNativeProperties();
}

bool UConsumableAbility_Invisible::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}