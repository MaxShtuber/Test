// Maxim Shtuber

#include "Components/TInventoryComponent.h"
#include "TCharacter.h"
#include "Objects/TInteractableActor.h"
#include "Objects/Weapons/TBaseWeapon.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UTInventoryComponent::UTInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UTInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTInventoryComponent::Interact()
{
	FHitResult HitResult;
	if (!LineTraceHitObject(HitResult)) return;

	auto Object = Cast<ATInteractableActor>(HitResult.Actor);
	if (!Object) return;

	if (!AddItemInInventory(Object)) return;

	Object->FinishInteraction(Cast<ATCharacter>(GetOwner()));
}

bool UTInventoryComponent::LineTraceHitObject(FHitResult& HitResult)
{
	FVector Start;
	FRotator StartRotator;
	FVector End;

	const auto Character = Cast<ATCharacter>(GetOwner());
	if (!Character) return false;

	const auto Controller = Character->Controller;
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(Start, StartRotator);
	End = Start + Controller->GetControlRotation().Vector() * MaxPickupDistance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 1.0f, 0, 3.0f);

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
	return HitResult.bBlockingHit;
}

bool UTInventoryComponent::AddItemInInventory(ATInteractableActor* Object)
{
	auto Data = Object->GetGeneralData();
	
	auto Weapon = Cast<ATBaseWeapon>(Object);
	bool AddAmmo = false;

	if (Weapon)
	{
		AddAmmo = AddItemInInventory(Weapon->GetAmmoData());
	}
	return AddItemInInventory(Data) || AddAmmo;
}

bool UTInventoryComponent::AddItemInInventory(const FObjectData& Data)
{
	auto MaxAmount = MaxInventory.Find(Data.ObjectClass);
	if (!MaxAmount) return false;

	auto CurrentAmount = Inventory.Find(Data.ObjectClass);

	if (CurrentAmount && *CurrentAmount == *MaxAmount)
	{
		return false;
	}
	else if (CurrentAmount)
	{
		*CurrentAmount = FMath::Clamp(*CurrentAmount + Data.Amount, 0, *MaxAmount);
	}
	else
	{
		Inventory.Add(Data.ObjectClass, 0);
		Inventory[Data.ObjectClass] = FMath::Clamp(Data.Amount, 0, *MaxAmount);
	}
	return true;
}

int32 UTInventoryComponent::RequestInventoryAmmo(TSubclassOf<ATInteractableActor>& Weapon, int32 Amount)
{
	int32& InventoryAmmo = *Inventory.Find(Weapon);
	if (InventoryAmmo >= Amount)
	{
		InventoryAmmo -= Amount;
	}
	else
	{
		Amount = InventoryAmmo;
		InventoryAmmo = 0;
	}
	return Amount;
	
}

int32 UTInventoryComponent::GetInventoryAmmo(TSubclassOf<ATInteractableActor>& Weapon) const
{
	return Inventory.Find(Weapon) ? *Inventory.Find(Weapon) : 0;

}