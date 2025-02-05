// Fill out your copyright notice in the Description page of Project Settings.


#include "PromptCollisionArea.h"

// Sets default values
APromptCollisionArea::APromptCollisionArea()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &APromptCollisionArea::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &APromptCollisionArea::OnOverlapEnd);

	PromptedItems.Init(nullptr,0);

	bISAvaliable = true;
}

void APromptCollisionArea::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APromptCollisionArea, bISAvaliable);
}

void APromptCollisionArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) 
{
	if (bISAvaliable) {
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player && Player->DamageCollision == OtherComp) {
			if (Player->IsPlayerOwner) {
				for (auto& item : PromptedItems)
				{
					item->Mesh->SetRenderCustomDepth(true);
					item->Mesh->SetCustomDepthStencilValue(OutlineColor);
					item->Mesh->MarkRenderStateDirty();
					Player->AddTargetArrowStatic(item);
				}
			}
		}
	}
}

void APromptCollisionArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bISAvaliable) {
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player && Player->DamageCollision == OtherComp) {
			if (Player->IsPlayerOwner) {
				for (auto& item : PromptedItems)
				{
					item->Mesh->SetRenderCustomDepth(false);
					item->Mesh->MarkRenderStateDirty();
					Player->RemoveTargetArrowStatic(item);
				}
			}
		}
	}
}

void APromptCollisionArea::SettingAvaliableFalse_Implementation()
{
	TArray<AActor*> Chels;
	GetOverlappingActors(Chels, AChel::StaticClass());
	for (auto& it : Chels) 
	{
		AChel* CurChel = Cast<AChel>(it);
		if (CurChel == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			for (int i = 0; i < PromptedItems.Num(); ++i) 
			{
				CurChel->RemoveTargetArrowStatic(PromptedItems[i]);
			}
		}
	}
}

void APromptCollisionArea::SettingAvaliableTrue_Implementation()
{
	TArray<AActor*> Chels;
	GetOverlappingActors(Chels, AChel::StaticClass());
	for (auto& it : Chels)
	{
		AChel* CurChel = Cast<AChel>(it);
		if (CurChel == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			for (int i = 0; i < PromptedItems.Num(); ++i)
			{
				CurChel->AddTargetArrowStatic(PromptedItems[i]);
			}
		}
	}
}
